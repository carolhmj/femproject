#include "points.h"
#include <iostream>

Points::Points()
{

}

Points::Points(std::vector<Vertex> vertices) :
    vertices(vertices)
{

}

void Points::addPoint(Vertex vertex)
{
    vertices.push_back(vertex);
}

void Points::initializePoints()
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

    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(vertices.data(), sizeof(Vertex) * vertices.size());

    glFuncs.glEnableVertexAttribArray(0);
    glFuncs.glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex),
                                (GLvoid*)0);
    glFuncs.glEnableVertexAttribArray(1);
    glFuncs.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                (GLvoid*)offsetof(Vertex, color));

    vao.release();
}

void Points::drawPoints(QOpenGLShaderProgram *program)
{
    program->bind();
    {
        vao.bind();
        glDrawArrays(GL_POINTS, 0, vertices.size());
        vao.release();
    }
    program->release();
}

