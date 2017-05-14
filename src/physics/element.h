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
#if USE_INTERFACE
#include <QOpenGLShaderProgram>
#endif

using std::vector;
using std::string;
using std::endl;

//Classe que representa um elemento. Possui uma lista de nós.
class Element
{
public:
    Element();
    //Funções reimplementadas por cada elemento
    virtual MatrixXd getLocalStiffnessMatrix() = 0;
    virtual MatrixXd getLocalMassMatrix() = 0;
    #if USE_INTERFACE
    virtual void draw(QOpenGLShaderProgram *program) = 0;
    virtual void drawLines(QOpenGLShaderProgram *program) = 0;
    #endif
    //Funções gerais
    virtual string printInfo();

    //Getters e setters
    Material *getMaterial() const;
    void setMaterial(Material *value);

    vector<Node *> getNodes() const;
    void setNodes(const vector<Node *> &value);

    unsigned int getNumNodes() const;

    Node *getNode(unsigned numNode);
protected:
    vector<Node*> nodes;
    Material *material;
    unsigned int numNodes;
};

#endif // ELEMENT_H
