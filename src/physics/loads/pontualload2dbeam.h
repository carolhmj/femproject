#ifndef PONTUALLOAD2D_H
#define PONTUALLOAD2D_H
#include "elementload.h"
#include <Eigen/Core>

using namespace Eigen;
//Classe que representa uma força pontual aplicada a um elemento
class PontualLoad2DBeam : public ElementLoad
{
public:
    PontualLoad2DBeam();
private:
    //Posição de aplicação da força
    Vector3d applicationPos;
    //Intensidade da força
    Vector3d intensity;
};

#endif // PONTUALLOAD2D_H
