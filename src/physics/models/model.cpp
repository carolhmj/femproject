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
    nodes(_nodes), elements(_elements), loads(_loads), name(_name)
{

}



MatrixXd Model::getGlobalStiffnessMatrix()
{
    //unsigned int totalDOFNumber = getTotalFreeDOFNumber();
    unsigned int totalDOFNumber = getTotalDOFNumber();
    std::cout << "total DOF number: " << totalDOFNumber << endl;
    MatrixXd G = MatrixXd::Zero(totalDOFNumber, totalDOFNumber);

   /* Manda a matriz de rigidez ser preenchida por cada elemento
    *
    */
    for (Element*& element : elements) {
        element->fillGlobalMatrix(G);
    }

    return G;
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

unsigned int Model::getTotalFreeDOFNumber()
{
    unsigned int totDof = 0;
    for (Node*& node : nodes) {
        totDof += node->getDOFNumber(RestrictionTypes::FREE);
    }
    return totDof;
}



