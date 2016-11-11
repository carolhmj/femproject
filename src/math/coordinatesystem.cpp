#include "coordinatesystem.h"

CoordinateSystem::CoordinateSystem()
{

}

CoordinateSystem::CoordinateSystem(Vector3d _x, Vector3d _y, Vector3d _z) :
    x(_x), y(_y), z(_z)
{

}

CoordinateSystem* CoordinateSystem::getSystemFromPoints(Vector3d eye, Vector3d at, Vector3d up)
{
    Vector3d x, y, z;
    x = (at - eye).normalized();
    z = x.cross(up - eye).normalized();
    y = z.cross(x);
    return new CoordinateSystem(x,y,z);
}

MatrixXd CoordinateSystem::transformTo()
{
    MatrixXd transformMatrix(3,3);

    transformMatrix << x[0], y[0], z[0],
                       x[1], y[1], z[1],
                       x[2], y[2], z[2];
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




