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
    numNodes = 2;
    //Encontra o sistema de coordenadas do elemento
    Vector3d x,y,z;
    x = (_n2->getPosition() - _n1->getPosition()).normalized();
    z = x.cross((upPoint - _n1->getPosition()).normalized());
    y = z.cross(x);
    coordinate = new CoordinateSystem(x,y,z);
    length = x.norm();
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

}

void BeamElement3D::draw()
{

}

