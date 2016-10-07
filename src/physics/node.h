#ifndef NODE_H
#define NODE_H
//Includes do modelo
#include "dof.h"
#include "nodeload.h"
//Includes de biblioteca
#include <Eigen/Core>
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::endl;

using namespace Eigen;
class Node
{
public:
    Node(Vector3d position, DOF* dof);
    Node(Vector3d position, std::vector<DOF*> dofs);
    void addDOF(DOF &dof);
    void draw();
    string printInfo();
    Vector3d getPosition();
private:
    vector<DOF*> dofs;
    Vector3d position;
};

#endif // NODE_H
