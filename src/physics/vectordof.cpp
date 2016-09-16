#include "vectordof.h"
#include <GL/gl.h>

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



