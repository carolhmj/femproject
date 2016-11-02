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

MatrixXd CoordinateSystem::transformTo()
{
    MatrixXd transformMatrix(3,3);
    transformMatrix << x[0], x[1], x[2],
                       y[0], y[1], y[2],
                       z[0], z[1], z[2];
    return transformMatrix;
}

std::string CoordinateSystem::printInfo()
{
    std::stringstream ss;
    ss << "¨¨¨¨¨ COORDINATE SYSTEM ¨¨¨¨¨¨" << endl;
    ss << "\t x: " << x.transpose() << endl;
    ss << "\t y: " << y.transpose() << endl;
    ss << "\t z: " << z.transpose() << endl;
    return ss.str();
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




