#ifndef VECTORDOF_H
#define VECTORDOF_H
//Includes do modelo
#include "dof.h"
#include "doftype.h"
#include "restrictiontypes.h"
//Includes de biblioteca
#include <Eigen/Core>
#include <vector>


using namespace Eigen;
//Grau de liberdade que é um vetor
class VectorDOF : public DOF
{
public:
    VectorDOF(VectorXd values, std::vector<VectorDOFType> types, std::vector<RestrictionTypes> restrictions, std::vector<int> equationNumbers);
    VectorXd getValues() const;
    std::vector<VectorDOFType> getTypes() const;
    std::vector<RestrictionTypes> getRestrictions() const;
    std::vector<int> getEquationNumbers() const;
    int getEquationNumber(unsigned int number);
    //Retorna todos os valores do grau de liberdade que correspondem a um determinado tipo
    VectorXd getVectorDOFByType(VectorDOFType type);
    std::string printInfo();

private:
    //Valores do grau de liberdade
    VectorXd values;
    //Tipos de cada grau
    std::vector<VectorDOFType> types;
    //Restrições de cada grau
    std::vector<RestrictionTypes> restrictions;
    //Número de equação (-1 representa que não há equação associada)
    std::vector<int> equationNumbers;
};

#endif // VECTORDOF_H
