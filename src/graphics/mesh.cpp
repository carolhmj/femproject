#include "mesh.h"
#include <stddef.h>

Mesh::Mesh()
{

}

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices)
{
    this->vertices = vertices;
    this->indices = indices;
}

void Mesh::initializeMesh(QOpenGLShaderProgram program)
{
    this->program = program;

    vao.create();
    vao.bind();

    vertexBuffer.create();
    if (!vertexBuffer.bind()) {
        return;
    }
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(vertices.data(), sizeof(vertices.data()));

    program.enableAttributeArray(0);
    program.setAttributeBuffer(0, GL_DOUBLE, offsetof(Vertex, position), 3, sizeof(Vertex));
    program.enableAttributeArray(1);
    program.setAttributeBuffer(0, GL_FLOAT, offsetof(Vertex, color), 3, sizeof(Vertex));

    vao.release();
}

void Mesh::drawMesh()
{
    program.bind();
    {
        vao.bind();
        glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0);
        vao.release();
    }
    program.release();
}

