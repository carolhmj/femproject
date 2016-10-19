#include "node.h"
#include "doftype.h"
#include "vectordof.h"
#include <sstream>
#include <GL/gl.h>

Node::Node(Vector3d position, DOF *dof) :
    position(position)
{
    dofs = vector<DOF*>();
    dofs.push_back(dof);
    ndofs = dof->getTotalDOFNumber();
}

Node::Node(Vector3d position, std::vector<DOF*> dofs) :
    dofs(dofs), position(position)
{
    ndofs = 0;
    for (DOF*& dof : dofs) {
        ndofs += dof->getTotalDOFNumber();
    }
}

void Node::draw()
{
    glBegin(GL_POINT);
        glVertex3f(position[0], position[1], position[2]);
    glEnd();
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
unsigned int Node::getDOFNumber() const
{
    return ndofs;
}

unsigned int Node::getDOFNumber(RestrictionTypes restriction) const
{
    unsigned count = 0;
    for (DOF* dof : dofs) {
        count += dof->getTotalDOFNumber(restriction);
    }
}

DOF *Node::getDOFByType(DOFType type)
{
    for (DOF*& dof : dofs) {
        if (dof->getType() == type) {
            return dof;
        }
    }
    return nullptr;
}


