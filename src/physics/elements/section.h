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
    Section(double _inMomY, double _inMomZ, double _polarInertiaMoment, double _inArea);
    string printInfo();

    double getInertiaMomentY() const;
    void setInertiaMomentY(double value);

    double getInertiaMomentZ() const;
    void setInertiaMomentZ(double value);

    double getArea() const;
    void setArea(double value);

    double getPolarInertiaMoment() const;
    void setPolarInertiaMoment(double value);

private:
    //Momento de inércia em torno do eixo Y
    double inertiaMomentY;
    //Momento de inércia em torno do eixo Z
    double inertiaMomentZ;
    //Momento polar de inércia
    double polarInertiaMoment;
    //Área
    double area;
};

#endif // SECTION_H
