#if USE_INTERFACE
#ifndef VERTEX_H
#define VERTEX_H

#include <Eigen/Dense>

using namespace Eigen;

//Simple class representing a vertice
//Has position and color information, for now
struct Vertex {
    Vector3d position;
    Vector3f color;
    Vertex(Vector3d position, Vector3f color = Vector3f(1.0,1.0,1.0)) {
        this->position = position;
        this->color = color;
    }
};

#endif // VERTEX_H
#endif // USE_INTERFACE
