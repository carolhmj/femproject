#include "coordinatesystem.h"

CoordinateSystem::CoordinateSystem()
{

}

CoordinateSystem::CoordinateSystem(Vector3d _x, Vector3d _y, Vector3d _z) :
    x(_x), y(_y), z(_z)
{

}

MatrixXd CoordinateSystem::transformTo(CoordinateSystem &to)
{
    return MatrixXd(1,1);
}

Vector3d CoordinateSystem::getX() const
{
    return x;
}
Vector3d CoordinateSystem::getY() const
{
    return y;
}
Vector3d CoordinateSystem::getZ() const
{
    return z;
}




