#include "section.h"
#include <sstream>

Section::Section()
{

}

Section::Section(double _inMomY, double _inMomZ, double _polarInertiaMoment, double _inArea) :
    inertiaMomentY(_inMomY), inertiaMomentZ(_inMomZ), polarInertiaMoment(_polarInertiaMoment), area(_inArea)
{

}

string Section::printInfo()
{
    std::stringstream ss;
    ss << "++++++ SECTION INFO ++++++" << endl;
    ss << "\t inertia moment Y: " << inertiaMomentY << endl;
    ss << "\t inertia moment Z: " << inertiaMomentZ << endl;
    ss << "\t polar inertia moment: " << polarInertiaMoment << endl;
    ss << "\t area: " << area << endl;
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
double Section::getArea() const
{
    return area;
}

void Section::setArea(double value)
{
    area = value;
}
double Section::getPolarInertiaMoment() const
{
    return polarInertiaMoment;
}

void Section::setPolarInertiaMoment(double value)
{
    polarInertiaMoment = value;
}





