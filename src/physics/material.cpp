#include "material.h"
#include <sstream>

Material::Material()
{

}

string Material::printInfo()
{
    std::stringstream ss;
    ss << "ºººººº MATERIAL INFO ºººººº" << std::endl;
    ss << "\t young modulus: " << youngModulus << std::endl;
    ss << "\t poisson coefficient: " << poissonCoefficient << std::endl;
    ss << "\t density: " << density << std::endl;
    return ss.str();
}

