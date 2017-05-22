#if USE_INTERFACE
#include "glwidget.h"
#include <QDebug>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include "graphics/mesh.h"
#include "beamelement3d.h"
#include "graphics/meshfunctions.h"

std::vector<Vertex> meshVertices = {
    Vertex(Vector3d(-1.0,-1.0,1.0), Vector3f(1.f,0.f,0.f)),
    Vertex(Vector3d(1.0,-1.0,1.0), Vector3f(0.f,1.f,0.f)),
    Vertex(Vector3d(1.0,1.0,1.0), Vector3f(0.f,0.f,1.f)),
    Vertex(Vector3d(-1.0,1.0,1.0), Vector3f(1.f,1.f,1.f)),
    Vertex(Vector3d(-1.0,-1.0,-1.0), Vector3f(1.f,0.f,0.f)),
    Vertex(Vector3d(1.0,-1.0,-1.0), Vector3f(0.f,1.f,0.f)),
    Vertex(Vector3d(1.0,1.0,-1.0), Vector3f(0.f,0.f,1.f)),
    Vertex(Vector3d(-1.0,1.0,-1.0), Vector3f(1.f,1.f,1.f))
};

std::vector<GLuint> meshIndices = {
    // front
    0, 1, 2,
    2, 3, 0,
    // top
    3, 2, 6,
    6, 7, 3,
    // back
    7, 6, 5,
    5, 4, 7,
    // bottom
    4, 5, 1,
    1, 0, 4,
    // left
    4, 0, 3,
    3, 7, 4,
    // right
    1, 5, 6,
    6, 2, 1
};

Mesh *meshTest = MeshFunctions::Sphere();

BeamElement3D *e8b1, *e8b2, *e8b3;
Model *m8;

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent), mouse(this->width()/2, this->height()/2) {
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
            return;
        }
        bool bindResult = m_program->bind();
        if (!bindResult) {
            qDebug() << "[Could not bind shader to context]\n";
            return;
        }

    }

    meshTest->initializeMesh();

    std::vector<VectorDOFType> e8n1types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e8n1restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e8n1equations = {-1,-1,-1,-1,-1,0};
    VectorDOF *e8n1v = new VectorDOF(e8n1types, e8n1restrictions, e8n1equations);
    Node *e8n1 = new Node(Vector3d(0.0,0.0,0.0), e8n1v);

    std::vector<VectorDOFType> e8n2types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e8n2restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e8n2equations = {1,2,-1,-1,-1,3};
    VectorDOF *e8n2v = new VectorDOF(e8n2types, e8n2restrictions, e8n2equations);
    Node *e8n2 = new Node(Vector3d(0.0,2.0,0.0), e8n2v);

    std::vector<VectorDOFType> e8n3types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e8n3restrictions = {RestrictionTypes::FREE, RestrictionTypes::FIXED,  RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e8n3equations = {4,-1,-1,-1,-1,5};
    VectorDOF *e8n3v = new VectorDOF(e8n3types, e8n3restrictions, e8n3equations);
    Node *e8n3 = new Node(Vector3d(2.0,2.0,0.0), e8n3v);

    std::vector<VectorDOFType> e8n4types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e8n4restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e8n4equations = {6,7,-1,-1,-1,8};
    VectorDOF *e8n4v = new VectorDOF(e8n4types, e8n4restrictions, e8n4equations);
    Node *e8n4 = new Node(Vector3d(2.0,0.0,0.0), e8n4v);
    vector<Node*> e8nvector = {e8n1, e8n2, e8n3, e8n4};

    //I = 0.036m^-4, A = 0.12m^2
    //Material: Concreto http://www.concrete.org.uk/fingertips-nuggets.asp?cmd=display&id=525
    Section *e8s1 = new Section(0, 0.0036, 0, 0.12, meshTest);
    Section *e8s2 = new Section(0, 0.0036, 0, 0.12, meshTest);
    Section *e8s3 = new Section(0, 0.0036, 0, 0.12, meshTest);
    Material *e8m = new Material(10E9, 0, 0, 0);

    e8b1 = new BeamElement3D(e8n1, e8n2, Vector3d(-1,0,0),  e8s1, e8m);
    e8b2 = new BeamElement3D(e8n2, e8n3, Vector3d(0,1,0),  e8s2, e8m);
    e8b3 = new BeamElement3D(e8n3, e8n4, Vector3d(1,0,0),  e8s3, e8m);
    vector<Element*> e8bvector = {e8b1, e8b2, e8b3};

    //Loads
    //Força no nó 2 é de 5000N
    NodeLoad *e8n2load = new NodeLoad(0.0,-5000.0,0.0,0.0,0.0,0.0, e8n2);
    //Força no nó 4 é de 3000N
    NodeLoad* e8n4load = new NodeLoad(0.0,-3000.0,0.0,0.0,0.0,0.0, e8n4);

    vector<NodeLoad*> e8lvector = {e8n2load, e8n4load};
    vector<ElementLoad*> e8levector;

    m8 = new Model("Simple Beam 3D Test 2", e8nvector, e8bvector, e8lvector, e8levector);
    meshTest->initializeMesh();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}

void GLWidget::paintGL(){
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Generate Model, View and Projection matrices and send them to our shader
//    Matrix4f projection = perspective(camera.fov*180/M_PI, (float)this->width()/ (float)this->height(), 0.1f, 100.0f);
    Matrix4f projection = ortho(-this->width()/50, this->width()/50, -this->height()/50, this->height()/50, 0.1f, 100.0f);
//    Matrix4f projection = Matrix4f::Identity();
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
    m8->drawLines(m_program);
//    meshTest->drawMesh(m_program);
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

Matrix4f GLWidget::ortho(float left, float right, float bottom, float top, float near, float far) {
    Matrix4f mProjectionMatrix = Matrix4f::Identity();

    mProjectionMatrix(0,0) = 2 / (right-left);
    mProjectionMatrix(1,1) = 2 / (top-bottom);
    mProjectionMatrix(2,2) = -2 / (far-near);
    mProjectionMatrix(0,3) = -(right+left) / (right-left);
    mProjectionMatrix(1,3) = -(top+bottom) / (top-bottom);
    mProjectionMatrix(2,3) = -(far+near)/ (far-near);

    return mProjectionMatrix;
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    std::cout << "\nRegistered key press\n";
    float moveCameraFactor = 0.5;
    Vector3f moveVector;
    float rotAngle = 45;

    switch (event->key()) {
    case Qt::Key_Up:
        moveVector = -camera.up;
        camera.eye += moveCameraFactor * moveVector;
        camera.at += moveCameraFactor * moveVector;
        break;
    case Qt::Key_Down:
        moveVector = camera.up;
        camera.eye += moveCameraFactor * moveVector;
        camera.at += moveCameraFactor * moveVector;
        break;
    case Qt::Key_Left:
        moveVector = camera.getDirection().cross(camera.up).normalized();
        camera.eye += moveCameraFactor * moveVector;
        camera.at += moveCameraFactor * moveVector;
        break;
    case Qt::Key_Right:
        moveVector = -camera.getDirection().cross(camera.up).normalized();
        camera.eye += moveCameraFactor * moveVector;
        camera.at += moveCameraFactor * moveVector;
        break;
    case Qt::Key_W:
        camera.rotateXPos(rotAngle);
        break;
    case Qt::Key_S:
        camera.rotateXPos(-rotAngle);
        break;
    case Qt::Key_D:
        camera.rotateYPos(rotAngle);
        break;
    case Qt::Key_A:
        camera.rotateYPos(-rotAngle);
        break;
    }

    std::cout << camera.printInfo();
    std::flush(std::cout);

    event->accept();
    this->repaint();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    mouse.pressed = true;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse.pressed) {
        //Get mouse position difference
        float deltaX = event->x() - mouse.lastX,
              deltaY = event->y() - mouse.lastY;

        mouse.lastX = event->x();
        mouse.lastY = event->y();



        this->repaint();

    } else {

        mouse.lastX = event->x();
        mouse.lastY = event->y();
    }
}
void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mouse.pressed = false;
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    std::cout << "\nRegistered wheel event\n";
    //Get scroll steps
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;
    std::cout << "numDegrees: " << numDegrees << " numSteps: " << numSteps << "\n";

    float zoomFactor = 1.0f;

    //Move the camera field of view according to number of steps
    if (camera.fov >= 1.0f && camera.fov <= 45.0f) {
        camera.fov -= zoomFactor * numSteps;
    }
    if (camera.fov < 1.0f) {
        camera.fov = 1.0f;
    }
    if (camera.fov > 90.0f) {
        camera.fov = 90.0f;
    }

    std::cout << camera.printInfo();
    std::flush(std::cout);

    event->accept();
    this->repaint();
}
#endif USE_INTERFACE
