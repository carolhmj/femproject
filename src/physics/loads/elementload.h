#ifndef ELEMENTLOAD_H
#define ELEMENTLOAD_H
#include "load.h"
#include "dofload.h"
#include <vector>

//Classe que representa uma força aplicada em um elemento
class ElementLoad : public Load
{
public:
    ElementLoad();
    //Transform the load in equivalent nodal loads
    virtual std::vector<DOFLoad*> transformToNodalLoads();
};

#endif // ELEMENTLOAD_H
