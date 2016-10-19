#include "beamelement2d.h"
#include <sstream>
#include <GL/gl.h>

BeamElement2D::BeamElement2D()
{

}

BeamElement2D::BeamElement2D(Section *_section, Material *_material) : section(_section)
{
    numNodes = 2;
    material = _material;
}

BeamElement2D::BeamElement2D(Node *_n1, Node *_n2, Section *_section, Material *_material) : section(_section)
{
    nodes.push_back(_n1);
    nodes.push_back(_n2);
    length = (_n1->getPosition()-_n2->getPosition()).norm();
    numNodes = 2;
    material = _material;
}

string BeamElement2D::printInfo() {
    std::stringstream ss;
    ss << "<<<<<< 2D BEAM ELEMENT >>>>>>" << endl;
    ss << Element::printInfo();
    ss << section->printInfo();
    return ss.str();
}
/* Cria a matriz de rigidez do elemento.
 *
 */
MatrixXd BeamElement2D::createLocalStiffnessMatrix()
{
    MatrixXd K = MatrixXd::Zero(6,6);
    double E = material->getYoungModulus(),
           I = section->getInertiaMomentZ(),
           L = length,
           A = section->getArea(),
           L2 = L*L,
           L3 = L*L*L;
    K << E*A/L,       0  ,      0  ,-E*A/L ,       0  ,      0  ,
            0 , 12*E*I/L3, 6*E*I/L2,    0  ,-12*E*I/L3, 6*E*I/L2,
            0 ,  6*E*I/L2, 4*E*I/L ,    0  , -6*E*I/L2, 2*E*I/L ,
        -E*A/L,       0  ,      0  , E*A/L ,       0  ,      0  ,
            0 ,-12*3*I/L3,-6*E*I/L2,    0  , 12*E*I/L3,-6*E*I/L2,
            0 ,  6*E*I/L2, 2*E*I/L ,    0  , -6*E*I/L2, 4*E*I/L ;
    return K;
}

void BeamElement2D::draw()
{
    Vector3d pos;
    glBegin(GL_LINES);
        for (Node*& n : nodes) {
            pos = n->getPosition();
            glVertex3f(pos[0], pos[1], pos[2]);
        }
    glEnd();
}
