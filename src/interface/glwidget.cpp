#include "glwidget.h"
#include <QDebug>
#include <cmath>
#include <Eigen/Dense>
#include "graphics/mesh.h"

std::vector<Vertex> meshVertices = {
    Vertex(Vector3d(0,0,0),Vector3f(1.f,1.f,0.f)),
    Vertex(Vector3d(0,0.5,0),Vector3f(1.f,0.f,0.f)),
    Vertex(Vector3d(-0.25,0.25,0),Vector3f(0.f,1.f,0.f)),
    Vertex(Vector3d(-0.25,-0.25,0),Vector3f(0.f,0.f,1.f)),
    Vertex(Vector3d(0.25,-0.25,0),Vector3f(0.f,1.f,1.f)),
    Vertex(Vector3d(0.25,0.25,0),Vector3f(1.0f,0.f,1.0f))
};

std::vector<GLuint> meshIndices = {
    0,1,5,
    0,2,1,
    0,3,2,
    0,4,3,
    0,5,4,
};

Mesh *meshTest = new Mesh(meshVertices, meshIndices);

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent) {
}

GLWidget::~GLWidget() {

}

void GLWidget::initializeGL(){

    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    {
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "../src/interface/shaders/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "../src/interface/shaders/simple.frag");
        bool linkResult = m_program->link();
        if (!linkResult) {
            qDebug() << "[Could not link shaders]\n" << m_program->log();
        }
        bool bindResult = m_program->bind();
        if (!bindResult) {
            qDebug() << "[Could not bind shader to context]\n";
            return;
        }

    }

    meshTest->initializeMesh();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}

void GLWidget::paintGL(){
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Generate Model, View and Projection matrices and send them to our shader
    Matrix4f projection = perspective(camera.fov*180/M_PI, (float)this->width()/ (float)this->height(), 0.1f, 100.0f);
    Matrix4f view = lookAt(camera.eye, camera.at, camera.up);
    Matrix4f model = Matrix4f::Identity();

    m_program->bind();
    GLint modelID = m_program->uniformLocation("model");
    if (modelID < 0) {
        qDebug() << "Uniform model doesn't exist in shader!\n";
    }
    glUniformMatrix4fv(modelID, 1, GL_FALSE, model.data());
    GLint viewID = m_program->uniformLocation("view");
    if (viewID < 0) {
        qDebug() << "Uniform view doesn't exist in shader!\n";
    }
    glUniformMatrix4fv(viewID, 1, GL_FALSE, view.data());
    GLint projectionID = m_program->uniformLocation("projection");
    if (projectionID < 0) {
        qDebug() << "Uniform projection doesn't exist in shader!\n";
    }
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, projection.data());
    m_program->release();

    // Render using our shader
    meshTest->drawMesh(m_program);
}

Matrix4f GLWidget::lookAt(const Vector3f& position, const Vector3f& target, const Vector3f& up)
{
  Matrix4f mViewMatrix = Matrix4f::Zero();

  Matrix3f R;
  R.col(2) = (position-target).normalized();
  R.col(0) = up.cross(R.col(2)).normalized();
  R.col(1) = R.col(2).cross(R.col(0));
  mViewMatrix.topLeftCorner<3,3>() = R.transpose();
  mViewMatrix.topRightCorner<3,1>() = -R.transpose() * position;
  mViewMatrix(3,3) = 1.0f;

  return mViewMatrix;
}

Matrix4f GLWidget::perspective(float fovY, float aspect, float near, float far)
{
  Matrix4f mProjectionMatrix = Matrix4f::Zero();

  float theta = fovY*0.5;
  float range = far - near;
  float invtan = 1./std::tan(theta);

  mProjectionMatrix(0,0) = invtan / aspect;
  mProjectionMatrix(1,1) = invtan;
  mProjectionMatrix(2,2) = -(near + far) / range;
  mProjectionMatrix(3,2) = -1;
  mProjectionMatrix(2,3) = -2 * near * far / range;
  mProjectionMatrix(3,3) = 0;

  return mProjectionMatrix;
}
