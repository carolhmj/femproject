#ifndef NODE_H
#define NODE_H
//Includes do modelo
#include "dof.h"
//Includes de biblioteca
#include <Eigen/Core>
#include <vector>
#include <string>

using namespace Eigen;
class Node
{
public:
    Node(DOF* dof);
    Node(std::vector<DOF*> dofs);
    void addDOF(DOF &dof);
    void draw();
    std::string printInfo();
    Vector3d getPosition();
private:
    std::vector<DOF*> dofs;
    Vector3d position;
};

#endif // NODE_H
