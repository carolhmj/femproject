#ifndef NODELOAD_H
#define NODELOAD_H

#include "load.h"
#include "node.h"
#include "loadcomponent.h"
#include "loadtype.h"
#include <vector>
#include <utility>

typedef std::pair<double, LoadType> ComponentAddPair;

//Class represents a nodal load. Has the associated node and the load components
class NodeLoad : public Load
{
public:
    NodeLoad();
    NodeLoad(double fx, double fy, double fz, double mx, double my, double mz, Node* node);
    void addToComponents(std::vector<ComponentAddPair> addComponents);
    string printInfo() override;

    //Getter
    Node *getNode() const;

    LoadComponent getComponents() const;

private:
    Node* node;
    LoadComponent components;
};

#endif // NODELOAD_H
