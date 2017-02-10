#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

#include <models/model.h>

class GLWidget : public QOpenGLWidget,
                 protected QOpenGLFunctions
{
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
private:
    //OpenGL drawing functions
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    // OpenGL State Information
    QOpenGLBuffer m_vertex;
    QOpenGLBuffer m_color;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;

    //Information for models
    std::vector<Model*> models;

};

#endif // GLWIDGET_H
