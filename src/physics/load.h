#ifndef LOAD_H
#define LOAD_H
#include "projectdefines.h"
#include "loadtype.h"

//Classe que representa uma força
class Load
{
public:
    Load();
    virtual string printInfo() = 0;
    LoadType getType() const;
    void setType(const LoadType &value);
protected:
    LoadType type;
};

#endif // LOAD_H
