#ifndef SECTION_H
#define SECTION_H
#include <string>
#include <iostream>
#if USE_INTERFACE
#include "graphics/mesh.h"
#endif
using std::string;
using std::endl;

//Classe que representa uma seção transversal
class Section
{
public:
    Section();
    Section(double _inMomY, double _inMomZ, double _polarInertiaMoment, double _inArea);
    #if USE_INTERFACE
    Section(double _inMomY, double _inMomZ, double _polarInertiaMoment, double _inArea, Mesh* mesh);
    void draw(QOpenGLShaderProgram *program, Eigen::Matrix4f modelMatrix = Eigen::Matrix4f::Identity());
    Mesh *getMesh() const;
    #endif

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
    #if USE_INTERFACE
    //Mesh, utilizado para desenhar a seção
    Mesh *mesh;
    #endif
};

#endif // SECTION_H
