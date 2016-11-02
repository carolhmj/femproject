#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "projectdefines.h"
#include <Eigen/Core>

using namespace Eigen;
/* Classe que representa um sistema de coordenadas. Os eixos do sistema são dados em termos do sistema de coordenadas
 * tradicional, com eixos em {1,0,0}, {0,1,0}, {0,0,1}
 */
class CoordinateSystem
{
public:
    CoordinateSystem();
    CoordinateSystem(Vector3d _x, Vector3d _y, Vector3d _z);
    // Retorna a matriz de transformação para o sistema de coordenadas dado como argumento
    MatrixXd transformTo(CoordinateSystem& to);
    // Retorna a matriz de transformação para o sistema tradicional
    MatrixXd transformTo();
    static CoordinateSystem getSystemFromPoints(Vector3d eye, Vector3d at, Vector3d up);
    string printInfo();

    Vector3d getX() const;

    Vector3d getY() const;

    Vector3d getZ() const;

private:
    Vector3d x;
    Vector3d y;
    Vector3d z;
};

#endif // COORDINATESYSTEM_H
