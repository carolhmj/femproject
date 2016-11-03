#include "beamelement3d.h"
#include <Eigen/Geometry>

BeamElement3D::BeamElement3D()
{

}

BeamElement3D::BeamElement3D(CoordinateSystem *_coordinate, Section *_section, Material *_material) :
    coordinate(_coordinate), section(_section)
{
    numNodes = 2;
    material = _material;
}

BeamElement3D::BeamElement3D(Node *_n1, Node *_n2, Vector3d upPoint, Section *_section, Material *_material) :
    section(_section)
{
    nodes.push_back(_n1);
    nodes.push_back(_n2);
    length = (_n2->getPosition() - _n1->getPosition()).norm();
    numNodes = 2;
    //Encontra o sistema de coordenadas do elemento
    Vector3d x, y, z;
    x = (_n2->getPosition() - _n1->getPosition()).normalized();
    z = x.cross(upPoint - _n1->getPosition()).normalized();
    y = z.cross(x);
    coordinate = new CoordinateSystem(x,y,z);
    material = _material;
}

std::string BeamElement3D::printInfo()
{
    std::stringstream ss;
    ss << "<<<<<< 3D BEAM ELEMENT >>>>>>" << endl;
    ss << "\tlength: " << length << endl;
    ss << Element::printInfo();
    ss << section->printInfo();
    return ss.str();
}

MatrixXd BeamElement3D::getLocalStiffnessMatrix()
{
    MatrixXd K = MatrixXd::Zero(12,12);
    float A = section->getArea(), E = material->getYoungModulus(),
          L = length, L2 = L*L, L3 =L*L, G = material->getShearModulus(),
          J = section->getPolarInertiaMoment(),
          IZ = section->getInertiaMomentZ(),
          IY = section->getInertiaMomentY(),
          a = E*A/L,
          b = 12*E*IZ/L3,
          c = 6*E*IZ/L3,
          d = 12*E*IY/L3,
          e = 6*E*IY/L2,
          f = G*J/L,
          g = 4*E*IY/L,
          h = 2*E*IY/L,
          i = 4*E*IZ/L,
          j = 2*E*IZ/L;

    MatrixXd block1 = MatrixXd::Zero(6,6), block2 = MatrixXd::Zero(6,6), block3, block4;
    block1(0,0) = a;
    block1(1,1) = b;
    block1(2,2) = d;
    block1(3,3) = f;
    block1(4,4) = g;
    block1(5,5) = i;
    block1(1,5) = c;
    block1(2,4) = -e;
    block1(4,2) = -e;
    block2(5,1) = c;


    block2(0,0) = -a;
    block2(1,1) = -b;
    block2(2,2) = -d;
    block2(3,3) = -f;
    block2(4,4) = h;
    block2(5,5) = j;
    block2(5,1) = -c;
    block2(4,2) = e;
    block2(2,4) = -e;
    block2(1,5) = c;

    block3 = block2;
    block3(1,5) = -block3(1,5);
    block3(5,1) = -block3(5,1);
    block3(2,4) = -block3(2,4);
    block3(4,2) = -block3(4,2);

    block4 = block1;
    block4(1,5) = -block4(1,5);
    block4(5,1) = -block4(5,1);
    block4(2,4) = -block4(2,4);
    block4(4,2) = -block4(4,2);


    K.block<6,6>(0,0) = block1;
    K.block<6,6>(0,6) = block2;
    K.block<6,6>(6,0) = block3;
    K.block<6,6>(6,6) = block4;

    std::cout << "K: " << endl << K << endl;

    MatrixXd transformMatrix = coordinate->transformTo();
    std::cout << "transformMatrix: " << endl << transformMatrix << endl;

    MatrixXd T(12,12);
    T.block<3,3>(0,0) = transformMatrix;
    T.block<3,3>(3,3) = transformMatrix;
    T.block<3,3>(6,6) = transformMatrix;
    T.block<3,3>(9,9) = transformMatrix;

//    std::cout << "T*K*T': " << endl << T*K*T.transpose() << endl;
//    return T*K*T.transpose();
    return K;
}

void BeamElement3D::draw()
{

}

