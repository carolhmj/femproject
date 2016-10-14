#ifndef MODEL_H
#define MODEL_H
//Model includes
#include "defines/projectdefines.h"
#include "node.h"
#include "element.h"
//Library includes

//Classe que representa um modelo. Possui os elementos e os nós do modelo
class Model
{
public:
    Model();
    Model(vector<Node*> _nodes, vector<Element*> _elements);
    Model(string _name, vector<Node*> _nodes, vector<Element*> _elements);
    //Calcula a matriz global a partir das matrizes locais de cada elemento
    MatrixXf getGlobalMatrix();
    void draw();
    string printInfo();
    void addNode(Node *_node);
    void addElement(Element *_element);
    vector<Node *> getNodes() const;
    vector<Element *> getElements() const;

private:
    vector<Node*> nodes;
    vector<Element*> elements;
    string name = string("Model");
};

#endif // MODEL_H
