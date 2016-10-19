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
    Section(double _inMomY, double _inMomZ, double _inArea);
    string printInfo();

    double getInertiaMomentY() const;
    void setInertiaMomentY(double value);

    double getInertiaMomentZ() const;
    void setInertiaMomentZ(double value);

    double getArea() const;
    void setArea(double value);

private:
    //Momento de inércia em torno do eixo Y
    double inertiaMomentY;
    //Momento de inércia em torno do eixo Z
    double inertiaMomentZ;
    //Área
    double area;
};

#endif // SECTION_H
