#include "vectordofload.h"
#include <sstream>

VectorDOFLoad::VectorDOFLoad()
{
<<<<<<< HEAD
<<<<<<< e6991e04dda80ae3cc347b2ec0729652f02330b6
    type = LoadType::NODE_LOAD;
=======
>>>>>>> Parte gráfica com modern OpenGL
=======
>>>>>>> f7489d678f097a56ccb135574329280a408d85aa
}

VectorDOFLoad::VectorDOFLoad(VectorDOF *_vectordof, VectorXd _values)
{
    assert(_values.rows() == _vectordof->getValues().rows());
    vdof = _vectordof;
    values = _values;
<<<<<<< HEAD
<<<<<<< e6991e04dda80ae3cc347b2ec0729652f02330b6
    type = LoadType::NODE_LOAD;
=======
>>>>>>> Parte gráfica com modern OpenGL
=======
>>>>>>> f7489d678f097a56ccb135574329280a408d85aa
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


