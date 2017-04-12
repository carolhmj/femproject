#ifndef NODE_H
#define NODE_H
//Includes do modelo
#include "dof.h"
#include "doftype.h"
//Includes de biblioteca
#include <Eigen/Core>
#include <vector>
#include <string>
#include <iostream>
#include "include/json.hpp"

using std::vector;
using std::string;
using std::endl;

using json = nlohmann::json;

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
    unsigned int getDOFNumber(RestrictionTypes restriction) const;
    DOF* getDOFByType(DOFType type);

private:
    vector<DOF*> dofs;
    Vector3d position;
    //Número de graus de liberdade que o nó possui no total
    unsigned int ndofs;
};

//Funções de conversão pra JSON
void to_json(json& j, const Node& p);
void from_json(const json& j, Node& p);

#endif // NODE_H
