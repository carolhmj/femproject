#ifndef SECTION_H
#define SECTION_H
#include <string>
#include <iostream>

using std::string;
using std::endl;

//Classe que representa uma seção transversal
class Section
{
public:
    Section();
    string printInfo();

    double getInertiaMomentY() const;
    void setInertiaMomentY(double value);

    double getInertiaMomentZ() const;
    void setInertiaMomentZ(double value);

private:
    double inertiaMomentY;
    double inertiaMomentZ;
};

#endif // SECTION_H
