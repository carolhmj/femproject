#include "mesh.h"
#include <stddef.h>
#include <QOpenGLFunctions>
#include <QDebug>

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
    initializeOpenGLFunctions();

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

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex),
                                (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                (GLvoid*)offsetof(Vertex, color));

    vao.release();
}

void Mesh::drawMesh(QOpenGLShaderProgram *program, Matrix4f modelMatrix)
{
    program->bind();
    glUniform4fv(program->uniformLocation("model"), 1, modelMatrix.data());
    {
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        vao.release();
    }
    program->release();
}
