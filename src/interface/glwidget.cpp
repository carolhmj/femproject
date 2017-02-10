#include "glwidget.h"
#include <QDebug>

static const GLfloat vertexes[] = {0.0f,0.0f,0.0f,
                                   0.0f,1.0f,0.0f,
                                   1.0f,1.0f,0.0f};

static const GLfloat vertexes2[] = {-1.0f,-1.0f,0.0f,
                                    -1.0f, 0.0f,0.0f,
                                     0.0f, 0.0f,0.0f,
                                     0.0f, 0.0f,0.0f,
                                     0.0f,-1.0f,0.0f,
                                    -1.0f,-1.0f,0.0f};


static const GLfloat colors[] = {0.0f,1.0f,0.5f,
                                 0.0f,1.0f,0.5f,
                                 0.0f,1.0f,0.5f};

static const GLfloat colors2[] = {0.0f,0.0f,0.6f,
                                  0.4f,0.0f,0.4f,
                                  0.2f,0.0f,0.5f,
                                  0.4f,0.3f,0.0f,
                                  0.1f,0.4f,0.4f,
                                  0.2f,0.3f,0.1f};

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent) {
}

GLWidget::~GLWidget() {

}

void GLWidget::initializeGL(){

    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

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

        m_program->release();
    }
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}

void GLWidget::paintGL(){
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render using our shader
    m_program->bind();
    {
        m_object.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_object.release();

        m_object2.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        m_object2.release();
    }
    m_program->release();
}
