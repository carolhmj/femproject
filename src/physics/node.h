#ifndef NODE_H
#define NODE_H
//Includes do modelo
#include "dof.h"
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
    unsigned int getDOFNumber() const;

private:
    vector<DOF*> dofs;
    Vector3d position;
    //Número de graus de liberdade que o nó possui no total
    unsigned int ndofs;
};

#endif // NODE_H
