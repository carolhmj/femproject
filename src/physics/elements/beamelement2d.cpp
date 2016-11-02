#include "beamelement2d.h"
#include <sstream>
#include <GL/gl.h>

BeamElement2D::BeamElement2D()
{

}

BeamElement2D::BeamElement2D(CoordinateSystem *_coordinate, Section *_section, Material *_material) :
    section(_section), coordinate(_coordinate)

{
    numNodes = 2;
    material = _material;
}

BeamElement2D::BeamElement2D(Node *_n1, Node *_n2, Vector3d upPoint, Section *_section, Material *_material) : section(_section)
{
    nodes.push_back(_n1);
    nodes.push_back(_n2);
    Vector3d x, y, z;
    x = (_n2->getPosition() - _n1->getPosition()).normalized();
    z = x.cross((upPoint - _n1->getPosition()).normalized());
    y = z.cross(x);
    coordinate = new CoordinateSystem(x,y,z);
    length = x.norm();

    numNodes = 2;
    material = _material;
}

string BeamElement2D::printInfo() {
    std::stringstream ss;
    ss << "<<<<<< 2D BEAM ELEMENT >>>>>>" << endl;
    ss << "\tlength: " << length << endl;
    ss << Element::printInfo();
    ss << section->printInfo();
    return ss.str();
}
/* Cria a matriz de rigidez do elemento.
 *
 */
MatrixXd BeamElement2D::getLocalStiffnessMatrix()
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

    MatrixXd transformMatrix = coordinate->transformTo();
    MatrixXd transformTo2dMatrix = MatrixXd::Zero(3,3);
    transformTo2dMatrix.block<2,2>(0,0) = transformMatrix.block<2,2>(0,0);
    transformTo2dMatrix(2,2) = transformMatrix(2,2);

//    std::cout << "transformTo2dMatrix: " << std::endl << transformTo2dMatrix << std::endl;
    MatrixXd transformToGlobalMatrix = MatrixXd::Zero(6,6);
    transformToGlobalMatrix.block<3,3>(0,0) = transformTo2dMatrix;
    transformToGlobalMatrix.block<3,3>(3,3) = transformTo2dMatrix;
    return transformToGlobalMatrix * K;
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
