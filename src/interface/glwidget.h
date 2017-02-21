#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <models/model.h>
#include <Eigen/Core>

using namespace Eigen;

struct Camera {
    Vector3f eye = Vector3f(0,0,5);
    Vector3f at = Vector3f(0,0,0);
    Vector3f up = Vector3f(0,1,0);
    float fov = 45.0f;
};

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

    //Matrix creation
    Matrix4f lookAt(const Vector3f& position, const Vector3f& target, const Vector3f& up);
    Matrix4f perspective(float fovY, float aspect, float near, float far);

    //World camera
    Camera camera;

    // OpenGL State Information    
    QOpenGLBuffer m_vertex;
    QOpenGLBuffer m_vertex2;
    QOpenGLBuffer m_color;
    QOpenGLBuffer m_color2;
    QOpenGLBuffer m_vertex3;
    QOpenGLBuffer m_color3;
    QOpenGLBuffer m_index3;

    QOpenGLVertexArrayObject m_object;
    QOpenGLVertexArrayObject m_object2;
    QOpenGLVertexArrayObject m_object3;
    QOpenGLShaderProgram *m_program;

    //Information for models
    std::vector<Model*> models;

};

#endif // GLWIDGET_H
