#ifndef SECTION_H
#define SECTION_H
#include <string>
#include <iostream>
#include <graphics/mesh.h>
#include "graphics/mesh.h"

using std::string;
using std::endl;

//Classe que representa uma seção transversal
class Section
{
public:
    Section();
    Section(double _inMomY, double _inMomZ, double _polarInertiaMoment, double _inArea);
    Section(double _inMomY, double _inMomZ, double _polarInertiaMoment, double _inArea, Mesh* mesh);

    void draw(QOpenGLShaderProgram *program, Eigen::Matrix4f modelMatrix = Eigen::Matrix4f::Identity());

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
    //Mesh, utilizado para desenhar a seção
    Mesh *mesh;
};

#endif // SECTION_H
