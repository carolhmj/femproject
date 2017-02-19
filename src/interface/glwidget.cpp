#include "glwidget.h"
#include <QDebug>

static const GLfloat vertexes[] = {0,0,0, 0,1,0, 1,1,0, 1,0,0};

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent) {
}

GLWidget::~GLWidget() {

}

void GLWidget::initializeGL(){
    glClearColor(0,0,0,1);

    //Falta botar os shaders
    {
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "../src/interface/shaders/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "../src/interface/shaders/simple.frag");
        bool linkResult = m_program->link();
        if (!linkResult) {
            qDebug() << "[Link error occurred!]\n" << m_program->log();
        }
        bool bindResult = m_program->bind();
        if (!bindResult) {
            qDebug() << "[Bind error occurred!]";
        }

        m_vertex.create();
        m_vertex.bind();
        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertex.allocate(vertexes, sizeof(vertexes));

        m_object.create();
        m_object.bind();
        m_program->enableAttributeArray(0);
        m_program->setAttributeArray(0, GL_FLOAT, vertexes, 3, 0);

        m_object.release();
        m_object.release();
        m_program->release();
    }
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}

void GLWidget::paintGL(){
    //Desenhar os modelos
    // Clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Render using our shader
    m_program->bind();
    {
        m_object.bind();
        glDrawArrays(GL_QUADS, 0, 4);
        m_object.release();
    }
    m_program->release();
}
