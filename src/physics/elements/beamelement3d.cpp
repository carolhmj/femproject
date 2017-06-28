#include "beamelement3d.h"
#include <Eigen/Geometry>

BeamElement3D::BeamElement3D()
{

}

BeamElement3D::BeamElement3D(CoordinateSystem *_coordinate, Section *_section, Material *_material) :
    coordinate(_coordinate)
{
    section = _section;
    numNodes = 2;
    material = _material;
}

BeamElement3D::BeamElement3D(Node *_n1, Node *_n2, Vector3d upPoint, Section *_section, Material *_material)
{
    section = _section;
    nodes.push_back(_n1);
    nodes.push_back(_n2);
    length = (_n2->getPosition() - _n1->getPosition()).norm();
    numNodes = 2;
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

//    std::cout << "E: " << E << " IZ " << IZ << " L3 " << L3 << endl;
//    std::cout << "12EIZ/L3: " << b << endl;
//    std::cout << "6EIZ/L2: " << c << endl;

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

//    std::cout << "block 2 before assign: " <<  endl << block2 << endl;

    //Mesmo que o bloco 2, só que a diagonal contrária é invertida
    block3 = block2;
    block3(1,5) = -block3(1,5);
    block3(5,1) = -block3(5,1);
    block3(2,4) = -block3(2,4);
    block3(4,2) = -block3(4,2);

//    std::cout << "block 2 before assign: " <<  endl << block2 << endl;

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

//    std::cout << "K: " << endl << K << endl;

    MatrixXd transformMatrix = coordinate->transformTo();
//    std::cout << "transformMatrix: " << endl << transformMatrix << endl;

    MatrixXd T = MatrixXd::Zero(12,12);
    T.block<3,3>(0,0) = transformMatrix;
    T.block<3,3>(3,3) = transformMatrix;
    T.block<3,3>(6,6) = transformMatrix;
    T.block<3,3>(9,9) = transformMatrix;

//    std::cout << "T: " << endl << T << endl;
//    std::cout << "T': " << endl << T.transpose() << endl;
//    std::cout << "T*K*T': " << endl << T*K*T.transpose() << endl;


    return T*K*T.transpose();
}

//Fonte da massa rotacional: http://kis.tu.kielce.pl/mo/COLORADO_FEM/colorado/IFEM.Ch31.pdf
MatrixXd BeamElement3D::getLocalMassMatrix()
{
    /* Constrói a matriz de massa através do método de lumped mass
     *
     */

    //Encontra a massa total do elemento = densidade * área * comprimento
    double totalMass = material->getDensity() * section->getArea() * length;

    //Cada nó vai ter 1/2 da massa total, e cada grau de liberdade vai ter esse valor de massa??? (perguntar)
    double halfMass = totalMass / 2.0;

    MatrixXd M = MatrixXd::Zero(12,12);
    for (int i = 0; i < 12; i++) {
        //Massa translacional
        if (i < 3 || (i >=6 && i <= 8) ) {
            M(i,i) = halfMass;
        } else {
            M(i,i) = totalMass * length * length * 2/50;
        }
    }

    //Não precisa de transformação pro sistema de coordenadas global, então retorna como está
    return M;
}

#if USE_INTERFACE
void BeamElement3D::draw(QOpenGLShaderProgram *program)
{
    /* Pra desenhar o elemento, primeiro vamos desenhar as seções
     * transversais. Para isso, temos que colocá-las nas posições
     * corretas em relação ao sistema de coordenadas do elemento.
     * Então, vamos criar uma matriz que muda do sistema local da
     * seção, para o sistema do elemento
     */

    /* Criamos um sistema de coordenadas para a seção, no qual o eixo x do
     * elemento é o eixo z da seção, e o eixo z do elemento é o eixo x da
     * seção
     */

    CoordinateSystem newCoords(coordinate->getZ(), coordinate->getY(), coordinate->getX());

    //Essa matrix rotaciona para o sistema correto de coordenadas.
//    Eigen::Matrix3f rotationPartial = coordinate->transformTo().cast<float>();
    Eigen::Matrix3f rotationPartial = newCoords.transformTo().cast<float>();

    Eigen::Matrix4f rotationFull = Matrix4f::Identity();
    rotationFull.block<3,3>(0,0) = rotationPartial;

    std::cout << "Rotation matrix:\n" << rotationFull << "\n";

    //Essa matrix translada para a origem - ou seja, o nó esquerdo
    Node *leftNode = nodes[0];
    Vector3d origin = leftNode->getPosition();
    Eigen::Affine3f translationAffine(Eigen::Translation3f(origin[0], origin[1], origin[2]));
    Matrix4f translation = translationAffine.matrix();

    std::cout << "Translation matrix left node:\n" << translation << "\n";

    Matrix4f transformation = translation * rotationFull;

    std::cout << "Transformation matrix:\n" << transformation << "\n";

    //Desenha primeira seção
    section->draw(program, transformation);

    //Essa matrix translada para o fim do eixo do nó - ou seja, o nó direito
    Node *rightNode = nodes[1];
    origin = rightNode->getPosition();
    translationAffine = Eigen::Affine3f(Eigen::Translation3f(origin[0], origin[1], origin[2]));
    translation = translationAffine.matrix();

    std::cout << "Translation matrix right node:\n" << translation << "\n";

    transformation = translation * rotationFull;

    std::cout << "Transformation matrix:\n" << transformation << "\n";

    //Desenha segunda seção
    section->draw(program, transformation);

    /* Agora, temos que desenhar as seções conectadas umas nas outras.
     * Uma possibilidade é criar uma nova seção com os vértices da primeira seção e os da segunda
     * rotacionados
     */

    std::vector<Vertex> beamVertices;
    std::vector<GLuint> beamIndices;

    std::vector<GLuint> sectionIndices = section->getMesh()->getIndices();

    for (auto& vertex : section->getMesh()->getVertices()) {
        beamVertices.push_back(vertex);
    }

    int biSize = beamIndices.size();
    for (int i = 0; i <= biSize; i = i+3) {
        beamIndices.push_back(sectionIndices[i]);
        beamIndices.push_back(sectionIndices[i]+biSize);
        beamIndices.push_back(sectionIndices[i+1]+biSize);
        beamIndices.push_back(sectionIndices[i+1]);

        beamIndices.push_back(sectionIndices[i]);
        beamIndices.push_back(sectionIndices[i]+biSize);
        beamIndices.push_back(sectionIndices[i+2]+biSize);
        beamIndices.push_back(sectionIndices[i+2]);

        beamIndices.push_back(sectionIndices[i+1]);
        beamIndices.push_back(sectionIndices[i+1]+biSize);
        beamIndices.push_back(sectionIndices[i+2]+biSize);
        beamIndices.push_back(sectionIndices[i+2]);
    }

    Vector3d posDiff = rightNode->getPosition() - leftNode->getPosition();
    Affine3f difference (Translation3f(posDiff(0),posDiff(1), posDiff(2)));
    Matrix4f translationMDiff = difference.matrix();
    Matrix4f transformDiff = translationMDiff;

    for (auto& vertex : section->getMesh()->getVertices()) {
        Vector4d vPos4 = Vector4d(vertex.position(0), vertex.position(1), vertex.position(2), 1.0);
        Vector4d vPosTrans = transformDiff.cast<double>() * vPos4;
        Vector3d transformed(vPosTrans(0), vPosTrans(1), vPosTrans(2));
        beamVertices.push_back(Vertex(transformed, vertex.color));
    }

    origin = leftNode->getPosition();
    translationAffine = Eigen::Affine3f(Eigen::Translation3f(origin[0], origin[1], origin[2]));
    translation = translationAffine.matrix();

    transformation = translation * rotationFull;

    Mesh *meshBeam = new Mesh(beamVertices, beamIndices);
    meshBeam->initializeMesh();
    meshBeam->drawMesh(program, transformation);
}

//O drawLines não se importa com a seção transversal do elemento, apenas desenha como se fosse uma linha
void BeamElement3D::drawLines(QOpenGLShaderProgram *program)
{
    Node *leftNode = nodes[0], *rightNode = nodes[1];
//    float t = length / 20.0;
    //Preciso encontrar um valor bom pra isso!
    //(Talvez o maior comprimento dividido por algum valor)
    float t = 0.02f;

    Vector3d posLeft = leftNode->getPosition(), posRight = rightNode->getPosition();
    Vector3d y = coordinate->getY(), z = coordinate->getZ();

    //Criar os pontos do paralelepípedo
    std::vector<Vertex> vertices;

    vertices.push_back(Vertex(posLeft + t*y + t*z, Vector3f(1,0,0)));
    vertices.push_back(Vertex(posLeft + t*y - t*z, Vector3f(0,1,0)));
    vertices.push_back(Vertex(posLeft - t*y - t*z, Vector3f(0,0,1)));
    vertices.push_back(Vertex(posLeft - t*y + t*z, Vector3f(1,1,0)));

    vertices.push_back(Vertex(posRight + t*y + t*z, Vector3f(0,1,1)));
    vertices.push_back(Vertex(posRight + t*y - t*z, Vector3f(1,0,1)));
    vertices.push_back(Vertex(posRight - t*y - t*z, Vector3f(0.5,0.5,0.5)));
    vertices.push_back(Vertex(posRight - t*y + t*z));

    //Criar as faces do paralelepípedo
    std::vector<GLuint> indices = {0,1,3,
                                   1,2,3, //Esquerda
                                   1,0,4,
                                   1,4,5, //Topo
                                   1,2,5,
                                   5,2,6, //Trás
                                   2,3,7,
                                   2,7,6, //Baixo
                                   0,3,4,
                                   4,3,7, //Frente
                                   5,4,7,
                                   5,7,6  //Direita
                                  };

    Mesh *elementMesh = new Mesh(vertices, indices);
    elementMesh->initializeMesh();
    elementMesh->drawMesh(program);
}
#endif
double BeamElement3D::getLength() const
{
    return length;
}

double BeamElement3D::getMass() const
{
    return material->getDensity() * section->getArea() * length;
}

double BeamElement3D::getVolume() const
{
    return section->getArea() * length;
}

Section *BeamElement3D::getSection() const
{
    return section;
}
CoordinateSystem *BeamElement3D::getCoordinate() const
{
    return coordinate;
}




