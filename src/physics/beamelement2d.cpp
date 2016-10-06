#include "beamelement2d.h"
#include <sstream>

BeamElement2D::BeamElement2D()
{

}

BeamElement2D::BeamElement2D(Section *section) : section(section)
{

}

string BeamElement2D::printInfo() {
    std::stringstream ss;
    ss << "<<<<<< 2D BEAM ELEMENT >>>>>>" << endl;
    ss << Element::printInfo();
    ss << section->printInfo();
    return ss.str();
}
