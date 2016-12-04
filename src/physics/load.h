#ifndef LOAD_H
#define LOAD_H
#include "projectdefines.h"

//Classe que representa uma força
class Load
{
public:
    Load();
    virtual string printInfo() = 0;
};

#endif // LOAD_H
