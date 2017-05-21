#ifndef MODEL_H
#define MODEL_H
//Model includes
#include "defines/projectdefines.h"
#include "node.h"
#include "element.h"
#include "load.h"
#include "nodeload.h"
#include "elementload.h"
#if USE_INTERFACE
#include "graphics/mesh.h"
#include "graphics/meshfunctions.h"
#endif //USE_INTERFACE
//Library includes
#include <QOpenGLShaderProgram>

//Classe que representa um modelo. Possui os elementos e os nós do modelo
class Model
{
public:
    Model();
    Model(vector<Node*> _nodes, vector<Element*> _elements, vector<NodeLoad*> _nloads, vector<ElementLoad*> _eloads);
    Model(string _name, vector<Node*> _nodes, vector<Element*> _elements, vector<NodeLoad *> _nloads, vector<ElementLoad*> _eloads);
    //Calcula a matriz de rigidez global a partir das matrizes locais de cada elemento
    MatrixXd getGlobalStiffnessMatrix();
    //Calcula a matriz de massa global
    MatrixXd getGlobalMassMatrix();
    //Calcula a matriz de massa global usando a lumped mass com aproximação da esfera
    MatrixXd getLumpedMassMatrix();
    //Calcula o vetor de forças
    VectorXd getGlobalForceVector();
#if USE_INTERFACE
    void draw(QOpenGLShaderProgram *program);
    void drawLines(QOpenGLShaderProgram *program);
#endif
    string printInfo();
    void addNode(Node *_node);
    void addElement(Element *_element);
    vector<Node *> getNodes() const;
    vector<Element *> getElements() const;
    void transformElementLoadsToNodeLoads();
    unsigned int getTotalDOFNumber();
    unsigned int getTotalFreeDOFNumber();
private:
    vector<Node*> nodes;
    vector<Element*> elements;
    vector<NodeLoad*> nodeLoads;
    vector<ElementLoad*> elementLoads;
    string name;
#if USE_INTERFACE
    //Drawing element
    Mesh *nodeMesh = MeshFunctions::Sphere();
#endif
};

#endif // MODEL_H
