#include "section.h"
#include <sstream>

Section::Section()
{

}

string Section::printInfo()
{
    std::stringstream ss;
    ss << "++++++ SECTION INFO ++++++" << endl;
    ss << "\t inertia moment Y: " << inertiaMomentY << endl;
    ss << "\t inertia moment Z: " << inertiaMomentZ << endl;
    return ss.str();
}
double Section::getInertiaMomentY() const
{
    return inertiaMomentY;
}

void Section::setInertiaMomentY(double value)
{
    inertiaMomentY = value;
}
double Section::getInertiaMomentZ() const
{
    return inertiaMomentZ;
}

void Section::setInertiaMomentZ(double value)
{
    inertiaMomentZ = value;
}



