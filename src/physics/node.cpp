#include "node.h"
#include "doftype.h"
#include "vectordof.h"
#include <sstream>

Node::Node(DOF *dof)
{
    dofs = vector<DOF*>();
    dofs.push_back(dof);
}

Node::Node(std::vector<DOF*> dofs) : dofs(dofs)
{

}

void Node::draw()
{

}

string Node::printInfo()
{
    std::stringstream output;
    output << "====== NODE INFO ======" << endl;
    output << "\t Position: " << position.transpose() << endl;
    output << "====== DOF INFO ======" << endl;
    for (DOF*& dof : dofs) {
        output << dof->printInfo();
    }
    return output.str();
}

Vector3d Node::getPosition()
{
    return position;
}

