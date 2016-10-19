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
    ndofs = dof->getNumber();
}

Node::Node(Vector3d position, std::vector<DOF*> dofs) :
    position(position), dofs(dofs)
{
    ndofs = 0;
    for (DOF*& dof : dofs) {
        ndofs += dof->getNumber();
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


