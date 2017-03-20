#ifndef BEAMELEMENT2D_H
#define BEAMELEMENT2D_H
#include "element.h"
#include "section.h"
#include "coordinatesystem.h"

//Subclasse de elemento que representa um elemento de viga 2 dimensional
class BeamElement2D : public Element
{
public:
    BeamElement2D();
    BeamElement2D(CoordinateSystem *_coordinate, Section *_section, Material *_material);
    BeamElement2D(Node *_n1, Node *_n2, Vector3d upPoint, Section *_section, Material *_material);
    string printInfo();
    MatrixXd getLocalStiffnessMatrix() override;
    void draw(QOpenGLShaderProgram *program) override;
    void drawLines(QOpenGLShaderProgram *program) override;
protected:
    Section *section;
    double length;
    CoordinateSystem *coordinate;
};

#endif // BEAMELEMENT2D_H
