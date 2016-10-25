#ifndef LOAD_H
#define LOAD_H
#include "projectdefines.h"
#include "loadtypes.h"
//Classe que representa uma força
class Load
{
public:
    Load();
    virtual string printInfo() = 0;
    virtual LoadTypes getType() const;
    void setType(const LoadTypes &value);

protected:
    LoadTypes type;
};

#endif // LOAD_H
