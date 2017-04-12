#ifndef ELEMENTLOAD_H
#define ELEMENTLOAD_H
#include "load.h"
#include "nodeload.h"
#include "loadcomponent.h"
#include "element.h"
#include <vector>
#include <QOpenGLShaderProgram>

//Classe que representa uma força aplicada em um elemento
class ElementLoad : public Load
{
public:
    ElementLoad();
    //Transform the load in equivalent nodal loads
    virtual std::pair<std::vector<ComponentAddPair>, std::vector<ComponentAddPair>> transformToNodalLoads() = 0;
    //Drawing
    virtual void draw(QOpenGLShaderProgram *program) = 0;
    virtual Element* getElement() = 0;
    virtual string printInfo() = 0;
};

#endif // ELEMENTLOAD_H
