#include "model.h"
#include <sstream>

Model::Model()
{

}

Model::Model(vector<Node *> _nodes, vector<Element *> _elements, vector<Load *> _loads) :
    nodes(_nodes), elements(_elements), loads(_loads), name("Model")
{

}

Model::Model(std::string _name, vector<Node *> _nodes, vector<Element *> _elements, vector<Load *> _loads) :
    name(_name), nodes(_nodes), elements(_elements), loads(_loads)
{

}



MatrixXf Model::getGlobalStiffnessMatrix()
{
    unsigned int totalDOFNumber = getTotalDOFNumber();
    MatrixXf G = MatrixXf::Zeros(totalDOFNumber, totalDOFNumber);

   /* Visita cada elemento, pega a matriz de rigidez, e para cada nó pega o número da equação dele
    *
    */
    for (Element*& element : elements) {

    }
}

void Model::draw()
{
    for (Node*& n : nodes){
        n->draw();
    }
    for (Element*& e : elements) {
        e->draw();
    }
}

std::string Model::printInfo()
{
    std::stringstream ss;
    ss << "@@@@@@ MODELO " << name << " @@@@@@" << endl;
    for (Node*& n : nodes){
        ss << n->printInfo();
    }
    for (Element*& e : elements) {
        ss << e->printInfo();
    }
    for (Load*& l : loads) {
        ss << l->printInfo();
    }
    return ss.str();
}

void Model::addNode(Node *_node) {
    nodes.push_back(_node);
}

void Model::addElement(Element *_element)
{
    elements.push_back(_element);
}

vector<Node *> Model::getNodes() const
{
    return nodes;
}
vector<Element *> Model::getElements() const
{
    return elements;
}

unsigned int Model::getTotalDOFNumber()
{
    unsigned int totDof = 0;
    for (Node*& node : nodes) {
        totDof += node->getDOFNumber();
    }
    return totDof;
}



