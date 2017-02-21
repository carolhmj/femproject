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

static const GLfloat vertexes[] = {0.0f,0.0f,0.0f,
                                   0.0f,1.0f,0.0f,
                                   1.0f,1.0f,0.0f};

static const GLfloat vertexes2[] = {-1.0f,-1.0f,0.0f,
                                    -1.0f, 0.0f,0.0f,
                                     0.0f, 0.0f,0.0f,
                                     0.0f, 0.0f,0.0f,
                                     0.0f,-1.0f,0.0f,
                                    -1.0f,-1.0f,0.0f};

GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f,  // Top Right
     0.5f, -0.5f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  // Bottom Left
    -0.5f,  0.5f, 0.0f   // Top Left
};

GLuint indices[] = {  // Note that we start from 0!
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
};

static const GLfloat colors[] = {0.0f,1.0f,0.5f,
                                 0.0f,1.0f,0.5f,
                                 0.0f,1.0f,0.5f};

static const GLfloat colors2[] = {0.0f,0.0f,0.6f,
                                  0.4f,0.0f,0.4f,
                                  0.2f,0.0f,0.5f,
                                  0.4f,0.3f,0.0f,
                                  0.1f,0.4f,0.4f,
                                  0.2f,0.3f,0.1f};

static const GLfloat colors3[] = {1.0f,0.0f,0.0f,
                                  0.0f,1.0f,0.0f,
                                  0.0f,0.0f,1.0f,
                                  0.5f,0.5f,0.5f};

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

        //Create and bind first VAO
        m_object.create();
        m_object.bind();

        m_vertex.create();
        bool vertexBindResult = m_vertex.bind();
        if (!vertexBindResult) {
            qDebug() << "[Could not bind vertex buffer to context]\n";
            return;
        }
        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertex.allocate(vertexes, sizeof(vertexes));

        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);

        m_color.create();
        bool colorBindResult = m_color.bind();
        if (!colorBindResult) {
            qDebug() << "[Could not bind color buffer to context]\n";
            return;
        }
        m_color.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_color.allocate(colors, sizeof(colors));

        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

        m_object.release();

        //Create and bind second VAO
        m_object2.create();
        m_object2.bind();

        m_vertex2.create();
        bool vertexBindResult2 = m_vertex2.bind();
        if (!vertexBindResult2) {
            qDebug() << "[Could not bind vertex buffer to context]\n";
            return;
        }
        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertex.allocate(vertexes2, sizeof(vertexes2));

        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);

        m_color2.create();
        bool colorBindResult2 = m_color2.bind();
        if (!colorBindResult2) {
            qDebug() << "[Could not bind color buffer to context]\n";
            return;
        }
        m_color.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_color.allocate(colors2, sizeof(colors2));

        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

        m_object2.release();

        //Create and bind third VAO
        m_object3.create();
        m_object3.bind();

        m_vertex3.create();
        bool vertexBindResult3 = m_vertex3.bind();
        if (!vertexBindResult3) {
            qDebug() << "[Could not bind vertex buffer to context]\n";
            return;
        }
        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertex.allocate(vertices, sizeof(vertices));

        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);

        m_color3.create();
        bool colorBindResult3 = m_color3.bind();
        if (!colorBindResult3) {
            qDebug() << "[Could not bind color buffer to context]\n";
            return;
        }
        m_color.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_color.allocate(colors3, sizeof(colors3));

        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

        m_index3 = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        m_index3.create();
        m_index3.bind();

        m_index3.allocate(indices, sizeof(indices));

        m_object3.release();

        m_program->release();
    }
    meshTest->initializeMesh();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}

void GLWidget::paintGL(){
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Generate Projection and Camera matrices
    Matrix4f projection = perspective(camera.fov*180/M_PI, (float)this->width()/ (float)this->height(), 0.1f, 100.0f);
    Matrix4f view = lookAt(camera.eye, camera.at, camera.up);
//    Matrix4f model = Matrix4f::Identity();
    Matrix4f model;
    float s = 3;
    model << s,0,0,0,
             0,s,0,0,
             0,0,s,0,
             0,0,0,1;
    Matrix4f mvp = projection * view * model;
//    Matrix4f mvp = Matrix4f::Identity();
    std::stringstream ss;
    ss << mvp;
    qDebug() << "MVP matrix:\n" << ss.str().c_str();
    // Render using our shader
    m_program->bind();

    GLint mvpID = m_program->uniformLocation("MVP");
    if (mvpID < 0) {
        qDebug() << "Uniform MVP doesn't exist in shader!\n";
    }
    //To send a uniform to the shader, you have to bind the program first!!!!
    glUniformMatrix4fv(mvpID, 1, GL_FALSE, mvp.data());

    {
//        m_object.bind();
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        m_object.release();

//        m_object2.bind();
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        m_object2.release();
//        m_object3.bind();
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    m_program->release();

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
