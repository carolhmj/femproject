#ifndef BEAMELEMENT2D_H
#define BEAMELEMENT2D_H
#include "element.h"
#include "section.h"

//Subclasse de elemento que representa um elemento de viga 2 dimensional
class BeamElement2D : public Element
{
public:
    BeamElement2D();
    BeamElement2D(Section *section);
    string printInfo();
private:
    Section *section;
};

#endif // BEAMELEMENT2D_H
