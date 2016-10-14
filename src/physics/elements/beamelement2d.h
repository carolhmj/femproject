#ifndef BEAMELEMENT2D_H
#define BEAMELEMENT2D_H
#include "element.h"
#include "section.h"

//Subclasse de elemento que representa um elemento de viga 2 dimensional
class BeamElement2D : public Element
{
public:
    BeamElement2D();
    BeamElement2D(Section *_section, Material *_material);
    BeamElement2D(Node *_n1, Node *_n2, Section *_section, Material *_material);
    string printInfo();
    MatrixXd createLocalStiffnessMatrix() override;
    void draw() override;
protected:
    Section *section;
};

#endif // BEAMELEMENT2D_H
