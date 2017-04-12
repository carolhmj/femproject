#ifndef NODELOAD_H
#define NODELOAD_H

//Model includes
#include "load.h"
#include "node.h"
#include "loadcomponent.h"
#include "loadtype.h"
//Library includes
#include <vector>
#include <utility>
#include <QOpenGLShaderProgram>

struct ComponentAddPair {
    double value;
    LoadType type;
    ComponentAddPair(double value, LoadType type) {
        this->value = value;
        this->type = type;
    }
};

//Class represents a nodal load. Has the associated node and the load components
class NodeLoad : public Load
{
public:
    NodeLoad();
    NodeLoad(double fx, double fy, double fz, double mx, double my, double mz, Node* node);
    void addToComponents(std::vector<ComponentAddPair> addComponents);
    string printInfo() override;

    //Drawing
    void draw(QOpenGLShaderProgram *program);

    //Getters
    Node *getNode() const;
    LoadComponent getComponents() const;

private:
    Node* node;
    LoadComponent components;
};

#endif // NODELOAD_H
