#ifndef VECTORDOF_H
#define VECTORDOF_H
//Includes do modelo
#include "dof.h"
#include "doftype.h"
#include "restrictiontypes.h"
#include <vector>
//Includes de biblioteca
#include <Eigen/Core>


using std::vector;
using std::string;
using std::endl;

using namespace Eigen;
//Grau de liberdade que é um vetor
class VectorDOF : public DOF
{
public:
    VectorDOF(VectorXd values, vector<VectorDOFType> types, vector<RestrictionTypes> restrictions, vector<int> equationNumbers);
    VectorDOF(vector<VectorDOFType> types, vector<RestrictionTypes> restrictions, vector<int> equationNumbers);
    VectorXd getValues() const;
    vector<VectorDOFType> getDOFTypes() const;
    vector<RestrictionTypes> getRestrictions() const;
    vector<int> getEquationNumbers() const;
    int getEquationNumber(unsigned int number) override;
    //Retorna todos os valores do grau de liberdade que correspondem a um determinado tipo
    VectorXd getVectorDOFByType(VectorDOFType type);
    string printInfo() override;
    unsigned int getTotalDOFNumber() override;
    unsigned int getTotalDOFNumber(RestrictionTypes restriction) override;

private:
    //Valores do grau de liberdade
    VectorXd values;
    //Tipos de cada grau
    vector<VectorDOFType> types;
    //Restrições de cada grau
    vector<RestrictionTypes> restrictions;
    //Número de equação (-1 representa que não há equação associada)
    vector<int> equationNumbers;
};

#endif // VECTORDOF_H
