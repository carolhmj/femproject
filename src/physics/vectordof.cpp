#include "vectordof.h"
#include <GL/gl.h>
#include <sstream>

VectorDOF::VectorDOF(VectorXd values, std::vector<VectorDOFType> types, std::vector<RestrictionTypes> restrictions) :
    values(values), types(types), restrictions(restrictions)
{
    setType(DOFType::VECTOR);
}
VectorXd VectorDOF::getValues() const
{
    return values;
}
std::vector<VectorDOFType> VectorDOF::getTypes() const
{
    return types;
}
std::vector<RestrictionTypes> VectorDOF::getRestrictions() const
{
    return restrictions;
}

//! Implementar o get equation number
int VectorDOF::getEquationNumber(unsigned int number)
{
    return 0;
}

VectorXd VectorDOF::getTranslationDOF()
{
    std::vector<double> tv;
    for (unsigned int i = 0; i < types.size(); i++) {
        if (types[i] == VectorDOFType::TRANSLATION) {
            tv.push_back(values[i]);
        }
    }
    Map<VectorXd> tdof(tv.data(), tv.size());
    return tdof;
}

std::__cxx11::string VectorDOF::printInfo()
{
    std::stringstream output;
    output << "------- VECTOR DOF -------" << std::endl;
    for (unsigned int i = 0; i < types.size(); i++) {
        output << "\t Value: " << values[i];
        if (types[i] == VectorDOFType::TRANSLATION) {
            output << " TRANSLATION ";
        } else if (types[i] == VectorDOFType::ROTATION) {
            output << " ROTATION ";
        }
        if (restrictions[i] == RestrictionTypes::FIXED) {
            output << " FIXED ";
        } else if (restrictions[i] == RestrictionTypes::FREE){
            output << " FREE ";
        }
        output << std::endl;
    }
    return output.str();
}



