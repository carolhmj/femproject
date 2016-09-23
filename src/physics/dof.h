#ifndef DOF_H
#define DOF_H
//Model includes
#include "doftype.h"
//Library includes
#include <string>

//Classe abstrata que representa graus de liberdade
class DOF
{
public:
    DOF();
    virtual DOFType getType();
    virtual void setType(DOFType value);
    virtual int getEquationNumber(unsigned int number) = 0;
    virtual std::string printInfo() = 0;

private:
    DOFType type;
};

#endif // DOF_H
