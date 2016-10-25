#include "load.h"

Load::Load()
{

}
LoadTypes Load::getType() const
{
    return type;
}
void Load::setType(const LoadTypes &value)
{
    type = value;
}



