#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <models/model.h>
#include <Eigen/Core>

using namespace Eigen;

struct Camera {
    Vector3f eye = Vector3f(0,0,3);
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

    //Camera control
    void keyPressEvent(QKeyEvent *event); //Translation control
    void mousePressEvent(QMouseEvent *event); //Rotation control
    void mouseReleaseEvent(QMouseEvent *event); //Rotation control
    void wheelEvent(QWheelEvent *event); //Zoom control

    //World camera
    Camera camera;

    // OpenGL State Information    
    QOpenGLShaderProgram *m_program;

    //Information for models
    std::vector<Model*> models;

};

#endif // GLWIDGET_H
