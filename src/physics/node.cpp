#include "node.h"
#include "doftype.h"
#include "vectordof.h"

Node::Node(DOF *&dof)
{
    dofs.push_back(dof);
}

Node::Node(std::vector<DOF*> dofs) : dofs(dofs)
{

}

void Node::printInfo()
{

}

VectorXd Node::getPosition()
{
    std::vector<double> posv;
    for (DOF*& dof : dofs) {
        if (dof->getType() == DOFType::VECTOR) {

            VectorDOF* vdof = static_cast<VectorDOF*>(dof);

            for (unsigned int i = 0; i < vdof->getTypes().size(); i++) {
                if (vdof->getTypes()[i] == VectorDOFType::TRANSLATION) {
                    posv.push_back(vdof->getValues()[i]);
                }
            }
        }
    }
    Map<VectorXd> pos(posv.data(), posv.size());
    return pos;
}

