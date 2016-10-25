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
    return K;
}

//Preenche os elementos da matriz local a partir dos elementos da matriz global
void BeamElement2D::fillGlobalMatrix(MatrixXd &globalMatrix)
{
    MatrixXd localMatrix = getLocalStiffnessMatrix();
    std::cout << "localMatrix: " << endl << localMatrix << endl;

    //Tem que transformar a matriz pelo sistema de coordenadas depois
    //Talvez seja bom guardar a localMatrix em uma variável pra não ter que recriar sempre

    Node *n1 = nodes[0],
         *n2 = nodes[1];
    VectorDOF* n1dof = static_cast<VectorDOF*>(n1->getDOFByType(DOFType::VECTOR));
    VectorDOF* n2dof = static_cast<VectorDOF*>(n2->getDOFByType(DOFType::VECTOR));

    for (unsigned i = 0; i < n1dof->getRestrictions().size(); i++) {
        //Se o grau de liberdade da linha é livre, então botamos ele na matriz
        if (n1dof->getRestrictions()[i] == RestrictionTypes::FREE) {
            unsigned n1dofPosRow = n1dof->getEquationNumber(i);
            for (unsigned j = 0; j < n1dof->getRestrictions().size(); j++) {
                if (n1dof->getRestrictions()[j] == RestrictionTypes::FREE) {
                    unsigned n1dofPosCol = n1dof->getEquationNumber(j);
                    globalMatrix(n1dofPosRow, n1dofPosCol) += localMatrix(i,j);
                    std::cout << "global matrix("<< n1dofPosRow << "," << n1dofPosCol << ") = localMatrix(" <<i << "," << j <<") = " << localMatrix(i,j) << endl;
                }
            }
        }
    }

    //O nó 2 está nas posições 3,4,5..., na matriz local
    for (unsigned i = 0; i < n2dof->getRestrictions().size(); i++) {
        //Se o grau de liberdade é livre, então botamos ele na matriz
        if (n2dof->getRestrictions()[i] == RestrictionTypes::FREE) {
            unsigned n2dofPosRow = n2dof->getEquationNumber(i);
            for (unsigned j = 0; j < n2dof->getRestrictions().size(); j++) {
                if (n2dof->getRestrictions()[j] == RestrictionTypes::FREE) {
                    unsigned n2dofPosCol = n2dof->getEquationNumber(j);
                    globalMatrix(n2dofPosRow, n2dofPosCol) += localMatrix(i+3,j+3);
                    std::cout << "global matrix("<< n2dofPosRow << "," << n2dofPosCol << ") = localMatrix(" << i+3 << "," << j+3 <<") = " << localMatrix(i+3,j+3) << endl;
                }
            }
        }
    }
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
