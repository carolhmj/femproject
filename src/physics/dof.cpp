#include "dof.h"

DOF::DOF()
{

}

DOFType DOF::getType()
{
    return type;
}
void DOF::setType(DOFType value)
{
    type = value;
}


