#include "vectordof.h"
#include <GL/gl.h>
#include <sstream>

VectorDOF::VectorDOF(VectorXd values, vector<VectorDOFType> types, vector<RestrictionTypes> restrictions, vector<int> equationNumbers) :
    values(values), types(types), restrictions(restrictions), equationNumbers(equationNumbers)
{
    setType(DOFType::VECTOR);
}

VectorDOF::VectorDOF(vector<VectorDOFType> types, vector<RestrictionTypes> restrictions, vector<int> equationNumbers) :
    types(types), restrictions(restrictions), equationNumbers(equationNumbers)
{
    assert(types.size() == restrictions.size() && restrictions.size() == equationNumbers.size());
    setType(DOFType::VECTOR);
    values = VectorXd::Zero(types.size());
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
//        switch (types[i]) {
//            case VectorDOFType::FX:
//                output << "TRANSLATION X";
//            break;
//            case VectorDOFType::FY:
//                output << "TRANSLATION Y";
//            break;
//            case VectorDOFType::FZ:
//                output << "TRANSLATION Z";
//            break;
//            case VectorDOFType::MX:
//                output << "MOMENT X";
//            break;
//            case VectorDOFType::MY:
//                output << "MOMENT Y";
//            break;
//            case VectorDOFType::MZ:
//                output << "MOMENT Z";
//            break;
//        }

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

unsigned int VectorDOF::getTotalDOFNumber()
{
    return values.rows();
}

//Conta o  número de DOFs com um determinado tipo de restrição
unsigned int VectorDOF::getTotalDOFNumber(RestrictionTypes restriction)
{
    unsigned int count = 0;
    for (RestrictionTypes DOFrestriction : restrictions) {
        if (DOFrestriction == restriction) {
            count++;
        }
    }
    return count;
}



