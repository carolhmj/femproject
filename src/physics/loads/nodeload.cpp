#include "nodeload.h"

NodeLoad::NodeLoad()
{

}

NodeLoad::NodeLoad(double fx, double fy, double fz, double mx, double my, double mz, Node *node)
{
    components = LoadComponent(fx,fy,fz,mx,my,mz);
    this->node = node;
}

void NodeLoad::addToComponents(std::vector<ComponentAddPair> addComponents)
{
    for (ComponentAddPair& pair : addComponents) {
        components.setValueByType(pair.value, pair.type);
    }
}

std::string NodeLoad::printInfo()
{
    std::stringstream ss;
    ss << "==== NodeLoad ====" << endl;
    ss << components.printInfo();
    return ss.str();
}

void NodeLoad::draw(QOpenGLShaderProgram *program)
{
    //Aqui vai ficar a função que desenha de acordo com as setas
}

Node *NodeLoad::getNode() const
{
    return node;
}
LoadComponent NodeLoad::getComponents() const
{
    return components;
}



