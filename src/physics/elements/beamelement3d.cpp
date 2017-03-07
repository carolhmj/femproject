#include "beamelement3d.h"
#include <Eigen/Geometry>

BeamElement3D::BeamElement3D()
{

}

BeamElement3D::BeamElement3D(CoordinateSystem *_coordinate, Section *_section, Material *_material) :
    coordinate(_coordinate), section(_section)
{
    numNodes = 2;
    material = _material;
}

BeamElement3D::BeamElement3D(Node *_n1, Node *_n2, Vector3d upPoint, Section *_section, Material *_material) :
    section(_section)
{
    nodes.push_back(_n1);
    nodes.push_back(_n2);
    length = (_n2->getPosition() - _n1->getPosition()).norm();
    numNodes = 2;
    //Encontra o sistema de coordenadas do elemento
//    Vector3d x, y, z;
//    x = (_n2->getPosition() - _n1->getPosition()).normalized();
//    z = x.cross(upPoint - _n1->getPosition()).normalized();
//    y = z.cross(x);
//    coordinate = new CoordinateSystem(x,y,z);
    coordinate = CoordinateSystem::getSystemFromPoints(_n1->getPosition(), _n2->getPosition(), upPoint);
    material = _material;
}

std::string BeamElement3D::printInfo()
{
    std::stringstream ss;
    ss << "<<<<<< 3D BEAM ELEMENT >>>>>>" << endl;
    ss << "\tlength: " << length << endl;
    ss << Element::printInfo();
    ss << section->printInfo();
    ss << coordinate->printInfo();
    return ss.str();
}

MatrixXd BeamElement3D::getLocalStiffnessMatrix()
{
    MatrixXd K = MatrixXd::Zero(12,12);
    float A = section->getArea(), E = material->getYoungModulus(),
          L = length, L2 = L*L, L3 =L*L*L, G = material->getShearModulus(),
          J = section->getPolarInertiaMoment(),
          IZ = section->getInertiaMomentZ(),
          IY = section->getInertiaMomentY(),
          a = E*A/L,
          b = 12*E*IZ/L3,
          c = 6*E*IZ/L2,
          d = 12*E*IY/L3,
          e = 6*E*IY/L2,
          f = G*J/L,
          g = 4*E*IY/L,
          h = 2*E*IY/L,
          i = 4*E*IZ/L,
          j = 2*E*IZ/L;

    std::cout << "E: " << E << " IZ " << IZ << " L3 " << L3 << endl;
    std::cout << "12EIZ/L3: " << b << endl;
    std::cout << "6EIZ/L2: " << c << endl;

    MatrixXd block1 = MatrixXd::Zero(6,6), block2 = MatrixXd::Zero(6,6), block3, block4;
    //EA/L
    block1(0,0) = a;
    //12EIZ/L3
    block1(1,1) = b;
    //12EIY/L3
    block1(2,2) = d;
    //GJ/L
    block1(3,3) = f;
    //4EIY/L
    block1(4,4) = g;
    //4EIZ/L
    block1(5,5) = i;
    //6EIZ/L2
    block1(1,5) = c;
    //6EIY/L2
    block1(2,4) = e;
    //6EIY/L2
    block1(4,2) = e;
    //6EIZ/L2
    block1(5,1) = c;


    //-EA/L
    block2(0,0) = -a;
    //-12EIZ/L3
    block2(1,1) = -b;
    //-12EIY/L3
    block2(2,2) = -d;
    //-GJ/L
    block2(3,3) = -f;
    //2EIY/L
    block2(4,4) = h;
    //2EIZ/L
    block2(5,5) = j;
    //6EIZ/L2
    block2(1,5) = c;
    //6EIY/L2
    block2(4,2) = e;
    //-6EIY/L2
    block2(2,4) = -e;
    //-6EIZ/L2
    block2(5,1) = -c;

    std::cout << "block 2 before assign: " <<  endl << block2 << endl;

    //Mesmo que o bloco 2, só que a diagonal contrária é invertida
    block3 = block2;
    block3(1,5) = -block3(1,5);
    block3(5,1) = -block3(5,1);
    block3(2,4) = -block3(2,4);
    block3(4,2) = -block3(4,2);

    std::cout << "block 2 before assign: " <<  endl << block2 << endl;

    //Mesmo que o bloco 1, só que a diagonal contrária é invertida
    block4 = block1;
    block4(1,5) = -block4(1,5);
    block4(5,1) = -block4(5,1);
    block4(2,4) = -block4(2,4);
    block4(4,2) = -block4(4,2);


    K.block<6,6>(0,0) = block1;
    K.block<6,6>(0,6) = block2;
    K.block<6,6>(6,0) = block3;
    K.block<6,6>(6,6) = block4;

    std::cout << "K: " << endl << K << endl;

    MatrixXd transformMatrix = coordinate->transformTo();
    std::cout << "transformMatrix: " << endl << transformMatrix << endl;

    MatrixXd T = MatrixXd::Zero(12,12);
    T.block<3,3>(0,0) = transformMatrix;
    T.block<3,3>(3,3) = transformMatrix;
    T.block<3,3>(6,6) = transformMatrix;
    T.block<3,3>(9,9) = transformMatrix;

    std::cout << "T: " << endl << T << endl;
    std::cout << "T': " << endl << T.transpose() << endl;
    std::cout << "T*K*T': " << endl << T*K*T.transpose() << endl;


    return T*K*T.transpose();
}

void BeamElement3D::draw(QOpenGLShaderProgram *program)
{
    /* Pra desenhar o elemento, primeiro vamos desenhar as seções
     * transversais. Para isso, temos que colocá-las nas posições
     * corretas em relação ao sistema de coordenadas do elemento.
     * Então, vamos criar uma matriz que muda do sistema local da
     * seção, para o sistema do elemento
     */

    //Essa matrix rotaciona para o sistema correto de coordenadas.
    Eigen::Matrix3f rotationPartial = coordinate->transformTo().cast<float>();

    Eigen::Matrix4f rotationFull = Matrix4f::Identity();
    rotationFull.block<3,3>(0,0) = rotationPartial;

    //Essa matrix translada para a origem - ou seja, o nó direito
    Node *leftNode = nodes[0];
    Vector3d origin = leftNode->getPosition();
    Eigen::Affine3f translationAffine(Eigen::Translation3f(origin[0], origin[1], origin[2]));
    Matrix4f translation = translationAffine.matrix();

    Matrix4f transformation = translation * rotationFull;

    //Desenha primeira seção
    section->draw(program, transformation);

}
double BeamElement3D::getLength() const
{
    return length;
}


