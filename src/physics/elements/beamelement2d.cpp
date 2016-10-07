#include "beamelement2d.h"
#include <sstream>

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

MatrixXd BeamElement2D::createLocalStiffnessMatrix()
{
    return MatrixXd();
}
