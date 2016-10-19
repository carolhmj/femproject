#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "projectdefines.h"
#include <Eigen/Core>

using namespace Eigen;
/* Classe que representa um sistema de coordenadas. Usado para converter do sistema local do elemento
 * para o sistema global
 */
class CoordinateSystem
{
public:
    CoordinateSystem();
    CoordinateSystem(Vector3d _x, Vector3d _y, Vector3d _z);
    //Retorna a matriz de transformação para o sistema de coordenadas
    MatrixXd transformTo(CoordinateSystem& to);
    Vector3d getX() const;

    Vector3d getY() const;

    Vector3d getZ() const;

private:
    Vector3d x;
    Vector3d y;
    Vector3d z;
};

#endif // COORDINATESYSTEM_H
