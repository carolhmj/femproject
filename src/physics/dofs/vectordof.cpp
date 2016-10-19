#include "vectordof.h"
#include <GL/gl.h>
#include <sstream>

VectorDOF::VectorDOF(VectorXd values, vector<VectorDOFType> types, vector<RestrictionTypes> restrictions, vector<int> equationNumbers) :
    values(values), types(types), restrictions(restrictions), equationNumbers(equationNumbers)
{
    setType(DOFType::VECTOR);
}
VectorXd VectorDOF::getValues() const
{
    return values;
}
vector<VectorDOFType> VectorDOF::getDOFTypes() const
{
    return types;
}
vector<RestrictionTypes> VectorDOF::getRestrictions() const
{
    return restrictions;
}

vector<int> VectorDOF::getEquationNumbers() const
{
    return equationNumbers;
}

int VectorDOF::getEquationNumber(unsigned int number)
{
    return equationNumbers[number];
}

VectorXd VectorDOF::getVectorDOFByType(VectorDOFType type)
{
    vector<double> tv;
    for (unsigned int i = 0; i < types.size(); i++) {
        if (types[i] == type) {
            tv.push_back(values[i]);
        }
    }
    Map<VectorXd> tdof(tv.data(), tv.size());
    return tdof;
}

string VectorDOF::printInfo()
{
    std::stringstream output;
    output << "------- VECTOR DOF -------" << endl;
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
        output << endl;
        output << "\t Equation number: " << equationNumbers[i];
        output << endl;
    }
    return output.str();
}

unsigned int VectorDOF::getNumber()
{
    return values.rows();
}



