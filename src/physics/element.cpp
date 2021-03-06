#include "element.h"
#include <sstream>

Element::Element()
{

}

Material *Element::getMaterial() const
{
    return material;
}

void Element::setMaterial(Material *value)
{
    material = value;
}
vector<Node *> Element::getNodes() const
{
    return nodes;
}

void Element::setNodes(const vector<Node *> &value)
{
    nodes = value;
}

unsigned int Element::getNumNodes() const
{
    return numNodes;
}

Node *Element::getNode(unsigned numNode)
{
    return nodes[numNode];
}

string Element::printInfo() {
    std::stringstream ss;
    ss << "==== ELEMENT INFO ===="  << endl;
    ss << material->printInfo();
    return ss.str();
}


