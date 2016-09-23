#include "node.h"
#include "doftype.h"
#include "vectordof.h"
#include <sstream>

Node::Node(DOF *dof)
{
    dofs = std::vector<DOF*>();
    dofs.push_back(dof);
}

Node::Node(std::vector<DOF*> dofs) : dofs(dofs)
{

}

void Node::draw()
{

}

std::__cxx11::string Node::printInfo()
{
    std::stringstream output;
    output << "====== NODE INFO ======" << std::endl;
    output << "====== DOF INFO ======" << std::endl;
    for (DOF*& dof : dofs) {
        //output << (int)dof->getType();
        output << dof->printInfo();
    }
    return output.str();
}

VectorXd Node::getPosition()
{

}

