#if USE_INTERFACE
#include "mesh.h"
#include <stddef.h>
#include <QOpenGLFunctions>
#include <QDebug>
#include <iostream>

Mesh::Mesh()
{
}

Mesh::Mesh(vector<Vertex> _vertices, vector<GLuint> _indices) :
    vertices(_vertices),
    indices(_indices)
{
}

void Mesh::initializeMesh()
{
    if (!QOpenGLContext::currentContext()) {
        std::cout << "No current OpenGL context" << std::endl;
        return;
    }
    glFuncs = QOpenGLFunctions(QOpenGLContext::currentContext());

    vao.create();
    vao.bind();

    vertexBuffer.create();
    if (!vertexBuffer.bind()) {
        qDebug() << "Could not bind vertex buffer to context\n";
        return;
    }

    elementBuffer.create();
    if (!elementBuffer.bind()) {
        qDebug() << "Could not bind element buffer to context\n";
        return;
    }

    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(vertices.data(), sizeof(Vertex) * vertices.size());

    elementBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    elementBuffer.allocate(indices.data(), sizeof(GLuint) * indices.size());

    glFuncs.glEnableVertexAttribArray(0);
    glFuncs.glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex),
                                (GLvoid*)0);
    glFuncs.glEnableVertexAttribArray(1);
    glFuncs.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                (GLvoid*)offsetof(Vertex, color));

    vao.release();
}

void Mesh::drawMesh(QOpenGLShaderProgram *program, Matrix4f modelMatrix)
{
    program->bind();
    glFuncs.glUniformMatrix4fv(program->uniformLocation("model"), 1, GL_FALSE, modelMatrix.data());
    {
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        vao.release();
    }
    program->release();
}
vector<Vertex> Mesh::getVertices() const
{
    return vertices;
}
vector<GLuint> Mesh::getIndices() const
{
    return indices;
}
#endif //USE_INTERFACE
