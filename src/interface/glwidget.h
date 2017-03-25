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
#include <sstream>
#include <Eigen/Geometry>

using namespace Eigen;

struct Camera {
    Vector3f eye = Vector3f(0,0,3);
    Vector3f at = Vector3f(0,0,0);
    Vector3f up = Vector3f(0,1,0);
    float fov = 45.0f;

    std::string printInfo() {
        std::stringstream info;
        info << "---------- CAMERA ---------------------------------------\n";
        info << "| fov: " << fov << "|\n";
        info << "| eye: " << eye.transpose() << "|\n";
        info << "| at: " << at.transpose() << "|\n";
        info << "| up: " << up.transpose() << "|\n";
        info << "----------------------------------------------------------\n";
        return info.str();
    }

    Vector3f getDirection() {
        return (at - eye).normalized();
    }

    void rotateYPos(float angle) {
        Transform<float, 3, Affine> rotationY;
        rotationY = AngleAxisf(angle * M_PI/180.0f, up);

        Vector4f eye4 = rotationY.matrix() * Vector4f(eye(0), eye(1), eye(2), 1.0f);
        Vector4f at4 = rotationY.matrix() * Vector4f(at(0), at(1), at(2), 1.0f);

        eye = eye4.head<3>();
        at = at4.head<3>();
    }

    void rotateXPos(float angle) {
        Transform<float, 3, Affine> rotationX;
        rotationX = AngleAxisf(angle * M_PI/180.0f, up.cross(getDirection()).normalized());

        Vector4f eye4 = rotationX.matrix() * Vector4f(eye(0), eye(1), eye(2), 1.0f);
        Vector4f at4 = rotationX.matrix() * Vector4f(at(0), at(1), at(2), 1.0f);

        eye = eye4.head<3>();
        at = at4.head<3>();
    }
};

struct Mouse {
    bool pressed = false;
    int lastX;
    int lastY;
    Mouse(int lastX, int lastY) {
        this->lastX = lastX;
        this->lastY = lastY;
    }
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
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event); //Zoom control

    //World camera
    Camera camera;

    //Mouse registering
    Mouse mouse;

    // OpenGL State Information    
    QOpenGLShaderProgram *m_program;

    //Information for models
    std::vector<Model*> models;

};

#endif // GLWIDGET_H
