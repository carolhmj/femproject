#ifndef ELEMENTLOAD_H
#define ELEMENTLOAD_H
#include "load.h"
#include "vectordofload.h"

//Classe que representa uma força aplicada em um elemento
class ElementLoad : public Load
{
public:
    ElementLoad();
    //Retorna as forças nodais equivalentes àquela força
    virtual VectorDOFLoad* getEquivalentNodal() = 0;
};

#endif // ELEMENTLOAD_H
