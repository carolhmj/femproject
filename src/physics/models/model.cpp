#include "model.h"
#include <sstream>
#include <typeinfo>
#include <Eigen/Geometry>

Model::Model()
{
    #if USE_INTERFACE
    nodeMesh->initializeMesh();
    #endif
}

Model::Model(vector<Node *> _nodes, vector<Element *> _elements, vector<NodeLoad *> _nloads, vector<ElementLoad *> _eloads) :
    nodes(_nodes), elements(_elements), nodeLoads(_nloads), elementLoads(_eloads), name("Model")
{
    #if USE_INTERFACE
    nodeMesh->initializeMesh();
    #endif
}

Model::Model(std::string _name, vector<Node *> _nodes, vector<Element *> _elements, vector<NodeLoad *> _nloads, vector<ElementLoad *> _eloads) :
    nodes(_nodes), elements(_elements), nodeLoads(_nloads), elementLoads(_eloads), name(_name)
{
    #if USE_INTERFACE
    nodeMesh->initializeMesh();
    #endif
}



MatrixXd Model::getGlobalStiffnessMatrix()
{
    unsigned int totalDOFNumber = getTotalFreeDOFNumber();
    std::cout << "[Model::getGlobalStiffnessMatrix()] total DOF number: " << totalDOFNumber << endl;
    MatrixXd G = MatrixXd::Zero(totalDOFNumber, totalDOFNumber);

   /*
    * Preenche a matriz de rigidez global a partir das matrizes locais
    */
    for (Element*& element : elements) {
//        element->fillGlobalMatrix(G);
        MatrixXd K = element->getLocalStiffnessMatrix();
        for (unsigned i = 0; i < element->getNumNodes(); i++) {
            Node *node = element->getNode(i);
            VectorDOF* dofvector = static_cast<VectorDOF*>(node->getDOFByType(DOFType::VECTOR));
            for (unsigned j = 0; j < dofvector->getTotalDOFNumber(); j++) {
                //Se o grau de liberdade é livre
                if (dofvector->getRestrictions()[j] == RestrictionTypes::FREE) {
                    unsigned localMatrixRowPos = i*dofvector->getTotalDOFNumber() + j;
                    unsigned dofPosRow = dofvector->getEquationNumber(j);
                    for (unsigned k = 0; k < element->getNumNodes(); k++) {
                        Node *node2 = element->getNode(k);
                        VectorDOF* dofvector2 = static_cast<VectorDOF*>(node2->getDOFByType(DOFType::VECTOR));
                        for (unsigned l = 0; l < dofvector2->getTotalDOFNumber(); l++) {
                            if (dofvector2->getRestrictions()[l] == RestrictionTypes::FREE) {
                                unsigned localMatrixColPos = k*dofvector2->getTotalDOFNumber() + l;
                                unsigned dofPosCol = dofvector2->getEquationNumber(l);
                                G(dofPosRow, dofPosCol) += K(localMatrixRowPos,localMatrixColPos);
                                std::cout << "global matrix("<< dofPosRow << "," << dofPosCol << ") = localMatrix(" << localMatrixRowPos << "," << localMatrixColPos <<") = " << K(localMatrixRowPos, localMatrixColPos) << endl;
                            }
                       }
                    }
                }
            }
        }
    }

    return G;
}

MatrixXd Model::getGlobalMassMatrix()
{
    unsigned int totalDOFNumber = getTotalFreeDOFNumber();
    std::cout << "[Model::getGlobalMassMatrix()] total DOF number: " << totalDOFNumber << endl;
    MatrixXd G = MatrixXd::Zero(totalDOFNumber, totalDOFNumber);

    //Percorre os elementos
    for (Element*& element : elements) {
        MatrixXd M = element->getLocalMassMatrix();
        for (unsigned i = 0; i < element->getNumNodes(); i++) {
            Node *node = element->getNode(i);
            VectorDOF* dofvector = static_cast<VectorDOF*>(node->getDOFByType(DOFType::VECTOR));
            for (unsigned j = 0; j < dofvector->getTotalDOFNumber(); j++) {
                //Se o grau de liberdade é livre
                if (dofvector->getRestrictions()[j] == RestrictionTypes::FREE) {
                    unsigned localMatrixRowPos = i*dofvector->getTotalDOFNumber() + j;
                    unsigned dofPosRow = dofvector->getEquationNumber(j);
                    for (unsigned k = 0; k < element->getNumNodes(); k++) {
                        Node *node2 = element->getNode(k);
                        VectorDOF* dofvector2 = static_cast<VectorDOF*>(node2->getDOFByType(DOFType::VECTOR));
                        for (unsigned l = 0; l < dofvector2->getTotalDOFNumber(); l++) {
                            if (dofvector2->getRestrictions()[l] == RestrictionTypes::FREE) {
                                unsigned localMatrixColPos = k*dofvector2->getTotalDOFNumber() + l;
                                unsigned dofPosCol = dofvector2->getEquationNumber(l);
                                //Preenchendo a matriz de massa
                                G(dofPosRow, dofPosCol) += M(localMatrixRowPos,localMatrixColPos);
                                //Caso o grau de liberdade seja de rotação
                                std::cout << "global matrix("<< dofPosRow << "," << dofPosCol << ") = localMatrix(" << localMatrixRowPos << "," << localMatrixColPos <<") = " << M(localMatrixRowPos, localMatrixColPos) << endl;
                            }
                       }
                    }
                }
            }
        }
    }
    return G;
}

MatrixXd Model::getLumpedMassMatrix()
{
    unsigned int totalDOFNumber = getTotalFreeDOFNumber();
    std::cout << "[Model::getLumpedMassMatrix()] total DOF number: " << totalDOFNumber << endl;
    MatrixXd G = MatrixXd::Zero(totalDOFNumber, totalDOFNumber);
    MatrixXd V = MatrixXd::Zero(totalDOFNumber, 2);

    for (Element*& element : elements) {
        double elementMass = element->getMass();
        double elementVolume = element->getVolume();

        for (unsigned i = 0; i < element->getNumNodes(); i++) {
            Node* node = element->getNode(i);
            VectorDOF* dofvector = static_cast<VectorDOF*>(node->getDOFByType(DOFType::VECTOR));
            for (unsigned j = 0; j < dofvector->getTotalDOFNumber(); j++) {
                if (dofvector->getRestrictions()[j] == RestrictionTypes::FREE) {
                    unsigned pos = dofvector->getEquationNumber(j);
                    G(pos, pos) += elementMass / 2.0;
                    //Pra preencher o rotational DOF, vamos salvar a soma dos volumes num vetor separado
                    //E também salvar quantos elementos somamos pra encontrar esse volume
                    if (dofvector->isRotationalDOF(j)) {
                        V(pos, 0) += elementVolume;
                        V(pos, 1) += 1;
                    }
                }
            }
        }
    }

    //Agora que G tem a soma de massas e V tem a soma dos volumes dos elementos que dão num certo nó, vamos descobrir a esfera equivalente
//    for (Element*& element : elements) {
//        for (unsigned i = 0; i < element->getNumNodes(); i++) {
//            Node* node = element->getNode(i);
//            VectorDOF* dofvector = static_cast<VectorDOF*>(node->getDOFByType(DOFType::VECTOR));
//            for (unsigned j = 0; j < dofvector->getTotalDOFNumber(); j++) {
//                if (dofvector->getRestrictions()[j] == RestrictionTypes::FREE) {
//                    if (dofvector->isRotationalDOF(j)) {
//                        unsigned pos = dofvector->getEquationNumber(j);
//                        std::cout << "pos: " << pos << "\n";
//                        double sphereVolume = V(pos, 0) / V(pos, 1);
//                        std::cout << "sphere volume: " << sphereVolume << "\n";
//                        //Esse volume tem que ser igual ao volume da esfera de raio r
//                        double sphereRadius = std::pow((4*M_PI)/(3*sphereVolume), 1.0/3.0);
//                        std::cout << "sphere radius: " << sphereRadius << "\n";
//                        std::cout << "mass: " << G(pos, pos) << "\n";
//                        //Depois de encontrar o raio, calculamos o momento de inércia da esfera:
//                        //https://en.wikipedia.org/wiki/List_of_moments_of_inertia
//                        double sphereInertia = 2*G(pos, pos)*sphereRadius*sphereRadius / 5.0;
//                        std::cout << "sphere inertia: " << sphereInertia << "\n";
//                        //A inércia da esfera que é a massa
//                        G(pos, pos) = sphereInertia;
//                    }
//                }
//            }
//        }
//    }

    for (int j = 0; j < V.rows(); j++) {
        unsigned pos = j;
        if (V(pos, 1) > 0) {
            std::cout << "pos: " << pos << "\n";
            double sphereVolume = V(pos, 0) / V(pos, 1);
            std::cout << "sphere volume: " << sphereVolume << "\n";
            //Esse volume tem que ser igual ao volume da esfera de raio r
            double sphereRadius = std::pow((4*M_PI)/(3*sphereVolume), 1.0/3.0);
            std::cout << "sphere radius: " << sphereRadius << "\n";
            std::cout << "mass: " << G(pos, pos) << "\n";
            //Depois de encontrar o raio, calculamos o momento de inércia da esfera:
            //https://en.wikipedia.org/wiki/List_of_moments_of_inertia
            double sphereInertia = 2*G(pos, pos)*sphereRadius*sphereRadius / 5.0;
            std::cout << "sphere inertia: " << sphereInertia << "\n";
            //A inércia da esfera que é a massa
            G(pos, pos) = sphereInertia;
        }
    }

    return G;
}

VectorXd Model::getGlobalForceVector()
{
    VectorXd f = VectorXd::Zero(getTotalFreeDOFNumber());
    //Itera pelos nós, para cada nó encontra a posição dele no force vector e coloca seus dofs no vetor
    for (NodeLoad*& nload : nodeLoads) {
        Node *node = nload->getNode();
        VectorDOF *vdof = static_cast<VectorDOF*>(node->getDOFByType(DOFType::VECTOR));

        for (unsigned i = 0; i < vdof->getTotalDOFNumber(); i++) {
            if (vdof->getRestrictions()[i] == RestrictionTypes::FREE) {
                f(vdof->getEquationNumber(i)) = nload->getComponents().getValue(i);
            }
        }
    }
    return f;
}

#if USE_INTERFACE
void Model::draw(QOpenGLShaderProgram *program)
{
    for (Node*& n : nodes){
        n->draw();
    }
    for (Element*& e : elements) {
        e->draw(program);
    }
}

void Model::drawLines(QOpenGLShaderProgram *program)
{
    double sizeFactor = 0.05;
    for (Node*& n : nodes) {
        Vector3d position = n->getPosition();
        Affine3f translation = Affine3f(Translation3f(position(0), position(1), position(2)));
        Affine3f scale = Affine3f(UniformScaling<float>(sizeFactor));

        nodeMesh->drawMesh(program, translation.matrix() * scale.matrix());
    }
    for (Element*& e : elements) {
        e->drawLines(program);
    }
}
#endif
std::string Model::printInfo()
{
    std::stringstream ss;
    ss << "@@@@@@ MODELO " << name << " @@@@@@" << endl;
    for (Node*& n : nodes){
        ss << n->printInfo();
    }
    for (Element*& e : elements) {
        ss << e->printInfo();
    }
    for (NodeLoad*& nl : nodeLoads) {
        ss << nl->printInfo();
    }
    for (ElementLoad*& el : elementLoads) {
        ss << el->printInfo();
    }
    return ss.str();
}

void Model::addNode(Node *_node) {
    nodes.push_back(_node);
}

void Model::addElement(Element *_element)
{
    elements.push_back(_element);
}

vector<Node *> Model::getNodes() const
{
    return nodes;
}
vector<Element *> Model::getElements() const
{
    return elements;
}

void Model::transformElementLoadsToNodeLoads()
{
    for (ElementLoad*& load : elementLoads) {
        //Get left and right addition components
        auto addCompVector = load->transformToNodalLoads();
        //Search for the nodal load that corresponds to the left and right nodes of the element
        for (NodeLoad*& nload : nodeLoads) {
            if (nload->getNode() == load->getElement()->getNode(0)) {
                nload->addToComponents(addCompVector.first);
            } else if (nload->getNode() == load->getElement()->getNode(1)) {
                nload->addToComponents(addCompVector.second);
            }
        }
    }
}

unsigned int Model::getTotalDOFNumber()
{
    unsigned int totDof = 0;
    for (Node*& node : nodes) {
        totDof += node->getDOFNumber();
    }
    return totDof;
}

unsigned int Model::getTotalFreeDOFNumber()
{
    unsigned int totDof = 0;
    for (Node*& node : nodes) {
        totDof += node->getDOFNumber(RestrictionTypes::FREE);
    }
    return totDof;
}



