#ifndef BEAMELEMENT3D_H
#define BEAMELEMENT3D_H

#include "element.h"
#include "section.h"
#include "coordinatesystem.h"

//Classe que representa um elemento de viga 3 dimensional
class BeamElement3D : public Element
{
public:
    BeamElement3D();
    BeamElement3D(CoordinateSystem *_coordinate, Section *_section, Material *_material);
    //Recebe os nós inicial e final, o ponto up, a seção e o material
    BeamElement3D(Node *_n1, Node *_n2,Vector3d upPoint, Section *_section, Material *_material);
    string printInfo();
    MatrixXd getLocalStiffnessMatrix() override;
    void draw() override;
protected:
    CoordinateSystem *coordinate;
    Section *section;
    double length;
};

#endif // BEAMELEMENT3D_H
