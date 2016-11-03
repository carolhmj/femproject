#include "material.h"
#include <sstream>

Material::Material()
{

}

Material::Material(double _youngModulus, double _shearModulus, double _poissonCoefficient, double _density) :
    youngModulus(_youngModulus), shearModulus(_shearModulus), poissonCoefficient(_poissonCoefficient), density(_density)
{

}

string Material::printInfo()
{
    std::stringstream ss;
    ss << "ºººººº MATERIAL INFO ºººººº" << std::endl;
    ss << "\t young modulus: " << youngModulus << std::endl;
    ss << "\t shear modulus: " << shearModulus << std::endl;
    ss << "\t poisson coefficient: " << poissonCoefficient << std::endl;
    ss << "\t density: " << density << std::endl;
    return ss.str();
}
double Material::getYoungModulus() const
{
    return youngModulus;
}
double Material::getPoissonCoefficient() const
{
    return poissonCoefficient;
}
double Material::getDensity() const
{
    return density;
}
double Material::getShearModulus() const
{
    return shearModulus;
}





