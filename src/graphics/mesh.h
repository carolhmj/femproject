#ifndef MESH_H
#define MESH_H

#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#include <GL/gl.h>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

using namespace Eigen;
using std::vector;

//Simple class representing a vertice
//Has position and color information, for now
struct Vertex {
    Vector3d position;
    Vector3f color;
    Vertex(Vector3d position, Vector3f color) {
        this->position = position;
        this->color = color;
    }
};

/* A class representing a triangle mesh. Has an
 * array of vertices and of triangle indices
 */
class Mesh
{
public:
    Mesh();
    Mesh(vector<Vertex> vertices, vector<GLuint> indices);
    void initializeMesh(QOpenGLShaderProgram program);
    void drawMesh();
private:
    //Mesh objects
    vector<Vertex> vertices;
    vector<GLuint> indices;
    //OpenGL array objects
    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer elementBuffer;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
};

#endif // MESH_H
