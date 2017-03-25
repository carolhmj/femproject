#ifndef MESH_H
#define MESH_H

#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#include <GL/gl.h>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "vertex.h"

using namespace Eigen;
using std::vector;

/* A class representing a triangle mesh. Has an
 * array of vertices and of triangle indices
 */
class Mesh //: protected QOpenGLFunctions
{
public:
    Mesh();
    Mesh(vector<Vertex> _vertices, vector<GLuint> _indices);
    void initializeMesh(/*QOpenGLFunctions *_glFuncs*/);
    void drawMesh(QOpenGLShaderProgram *program, Matrix4f modelMatrix = Matrix4f::Identity());
    vector<Vertex> getVertices() const;

    vector<GLuint> getIndices() const;

private:
    //Mesh objects
    vector<Vertex> vertices;
    vector<GLuint> indices;
    //OpenGL array objects
    QOpenGLBuffer vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer elementBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
    QOpenGLFunctions glFuncs;
};

#endif // MESH_H
