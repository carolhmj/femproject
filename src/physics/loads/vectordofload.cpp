#include "vectordofload.h"
#include <sstream>

VectorDOFLoad::VectorDOFLoad()
{
    //setType(LoadTypes::VECTORDOFLOAD);
}

VectorDOFLoad::VectorDOFLoad(VectorDOF *_vectordof, VectorXd _values)
{
    assert(_values.rows() == _vectordof->getValues().rows());
    vdof = _vectordof;
    values = _values;
    //setType(LoadTypes::VECTORDOFLOAD);
}

std::string VectorDOFLoad::printInfo()
{
    std::stringstream ss;
    ss << "==== VectorDOFLoad ====" << endl;
    for (int i = 0; i < values.rows(); i++){
        ss << "\t Value: " << values[i];
        if (vdof->getDOFTypes()[i] == VectorDOFType::TRANSLATION) {
            ss << " TRANSLATION ";
        } else if (vdof->getDOFTypes()[i] == VectorDOFType::ROTATION) {
            ss << " ROTATION ";
        }
        ss << "Equation number: " << vdof->getEquationNumber(i);
        ss << endl;
    }
    return ss.str();
}
VectorDOF *VectorDOFLoad::getVdof() const
{
    return vdof;
}

double VectorDOFLoad::getValue(unsigned i) const
{
    return values[i];
}


