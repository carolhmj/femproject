#if USE_INTERFACE
#ifndef POINTS_H
#define POINTS_H

#include <vector>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include "vertex.h"

/* Class representing a collection of points. Used to draw the
 * nodes
 */
class Points
{
public:
    Points();
    Points(std::vector<Vertex> vertices);

    void addPoint(Vertex vertex);

    void initializePoints();
    void drawPoints(QOpenGLShaderProgram *program);

private:
    //Mesh objects
    std::vector<Vertex> vertices;

    //OpenGL objects
    QOpenGLBuffer vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLVertexArrayObject vao;
    QOpenGLFunctions glFuncs;
};

#endif // POINTS_H
#endif //USE_INTERFACE
