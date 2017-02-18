#ifndef MODEL_H
#define MODEL_H
//Model includes
#include "defines/projectdefines.h"
#include "node.h"
#include "element.h"
#include "load.h"
#include "nodeload.h"
#include "elementload.h"
//Library includes

//Classe que representa um modelo. Possui os elementos e os nós do modelo
class Model
{
public:
    Model();
    Model(vector<Node*> _nodes, vector<Element*> _elements, vector<NodeLoad*> _nloads, vector<ElementLoad*> _eloads);
    Model(string _name, vector<Node*> _nodes, vector<Element*> _elements, vector<NodeLoad *> _nloads, vector<ElementLoad*> _eloads);
    //Calcula a matriz global a partir das matrizes locais de cada elemento
    MatrixXd getGlobalStiffnessMatrix();
    VectorXd getGlobalForceVector();
    void draw();
    string printInfo();
    void addNode(Node *_node);
    void addElement(Element *_element);
    vector<Node *> getNodes() const;
    vector<Element *> getElements() const;
    unsigned int getTotalDOFNumber();
    unsigned int getTotalFreeDOFNumber();
private:
    vector<Node*> nodes;
    vector<Element*> elements;
    vector<NodeLoad*> nodeLoads;
    vector<ElementLoad*> elementLoads;
    string name;
};

#endif // MODEL_H
