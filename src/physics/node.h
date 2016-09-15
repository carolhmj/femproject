#ifndef NODE_H
#define NODE_H
//Includes do modelo
#include "dof.h"
//Includes de biblioteca
#include <eigen3/Eigen/Core>
#include <vector>

using namespace Eigen;
class Node
{
public:
    Node(DOF* &dof);
    Node(std::vector<DOF*> dofs);
    void addDOF(DOF &dof);
    void draw();
    void printInfo();
    VectorXd getPosition();
private:
    std::vector<DOF*> dofs;
};

#endif // NODE_H
