#include "load.h"

Load::Load()
{

}
LoadType Load::getType() const
{
    return type;
}

void Load::setType(const LoadType &value)
{
    type = value;
}

