#ifndef ELEMENT_H
#define ELEMENT_H
//Model includes
#include "node.h"
#include "material.h"
#include "vectordof.h"
#include <vector>
#include <iostream>
#include <string>
#include <Eigen/Core>

using std::vector;
using std::string;
using std::endl;

//Classe que representa um elemento. Possui uma lista de nós.
class Element
{
public:
    Element();
    //Funções reimplementadas por cada elemento
    virtual MatrixXd createLocalStiffnessMatrix() = 0;
    virtual void draw() = 0;

    //Funções gerais
    virtual string printInfo();
    virtual void fillGlobalMatrix(MatrixXd &globalMatrix /*CoordinateSystem cs*/) = 0;

    //Getters e setters
    Material *getMaterial() const;
    void setMaterial(Material *value);

    vector<Node *> getNodes() const;
    void setNodes(const vector<Node *> &value);

protected:
    vector<Node*> nodes;
    Material *material;
    unsigned int numNodes;
};

#endif // ELEMENT_H
