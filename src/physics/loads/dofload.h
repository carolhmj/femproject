#ifndef DOFLOAD_H
#define DOFLOAD_H
#include "load.h"
//Classe que representa uma força em um grau de liberdade.
class DOFLoad : public Load
{
public:
    DOFLoad();
};

#endif // DOFLOAD_H
