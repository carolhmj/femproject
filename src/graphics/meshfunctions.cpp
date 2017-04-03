#include "meshfunctions.h"
#include <iostream>
#include "math/auxfunctions.h"

//Create a sphere mesh centered in position (0,0,0) with radius 1. Based on Three.js sphere
//generation algorithm
Mesh *MeshFunctions::Sphere()
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    int heightSegments = 8;
    int widthSegments = 6;
    double phiStart = 0;
    double phiLength = M_PI * 2;

    double thetaStart = 0;
    double thetaLength = M_PI;

    double thetaEnd = thetaStart + thetaLength;

    int grid[heightSegments][widthSegments];
    int index = 0;

    double distanceToCenter = 0.0;

    for (int iy = 0; iy <= heightSegments; iy ++ ) {

        double v = (double)iy / (double)heightSegments;


        for (int ix = 0; ix <= widthSegments; ix ++ ) {

            double u = (double)ix / (double)widthSegments;

            // vertex

            double x = AuxFunctions::clampToZero(- std::cos( phiStart + u * phiLength ) * std::sin( thetaStart + v * thetaLength ));
            double y = AuxFunctions::clampToZero(std::cos( thetaStart + v * thetaLength ));
            double z = AuxFunctions::clampToZero(std::sin( phiStart + u * phiLength ) * std::sin( thetaStart + v * thetaLength ));

            vertices.push_back(Vertex(Vector3d(x,y,z)));
            grid[iy][ix] = index++;

            std::cout << "u: [" << u << "] v: [" << v << "] (" << x << ", " << y << ", " << z << ")\n";
            distanceToCenter += (Vector3d(x,y,z)-Vector3d(0,0,0)).norm();
        }
    }

    std::cout << "medium distance to center: " << distanceToCenter / (double)(widthSegments * heightSegments) << "\n";
    std::flush(std::cout);

    // indices

    for (int iy = 0; iy < heightSegments; iy ++ ) {

        for (int ix = 0; ix < widthSegments; ix ++ ) {

            int a = grid[ iy ][ ix + 1 ];
            int b = grid[ iy ][ ix ];
            int c = grid[ iy + 1 ][ ix ];
            int d = grid[ iy + 1 ][ ix + 1 ];

            if ( iy != 0 || thetaStart > 0 ) {
                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(d);
            }
            if ( iy != heightSegments - 1 || thetaEnd < M_PI ) {
                indices.push_back(b);
                indices.push_back(c);
                indices.push_back(d);
            }
        }

    }

    return new Mesh(vertices, indices);

}
