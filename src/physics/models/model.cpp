#include "model.h"
#include <sstream>

Model::Model()
{

}

Model::Model(vector<Node *> _nodes, vector<Element *> _elements) :
    nodes(_nodes), elements(_elements)
{

}

Model::Model(std::string _name, vector<Node *> _nodes, vector<Element *> _elements) :
    name(_name), nodes(_nodes), elements(_elements)
{

}



MatrixXf Model::getGlobalMatrix()
{

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



