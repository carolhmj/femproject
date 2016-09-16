#ifndef VECTORDOF_H
#define VECTORDOF_H
//Includes do modelo
#include "dof.h"
#include "doftype.h"
//Includes de biblioteca
#include <eigen3/Eigen/Core>
#include <vector>


using namespace Eigen;
//Grau de liberdade que é um vetor
class VectorDOF : public DOF
{
public:
    VectorDOF(VectorXd values, std::vector<VectorDOFType> types, std::vector<int> restrictions);
    VectorXd getValues() const;
    std::vector<VectorDOFType> getTypes() const;
    std::vector<int> getRestrictions() const;

private:
    //Valores do grau de liberdade
    VectorXd values;
    //Tipos de cada grau
    std::vector<VectorDOFType> types;
    //Restrições de cada grau
    std::vector<int> restrictions;
};

#endif // VECTORDOF_H
