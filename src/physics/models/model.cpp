#include "model.h"
#include "vectordofload.h"
#include <sstream>
#include <typeinfo>


Model::Model()
{

}

Model::Model(vector<Node *> _nodes, vector<Element *> _elements, vector<Load *> _loads) :
    nodes(_nodes), elements(_elements), loads(_loads), name("Model")
{

}

Model::Model(std::string _name, vector<Node *> _nodes, vector<Element *> _elements, vector<Load *> _loads) :
    nodes(_nodes), elements(_elements), loads(_loads), name(_name)
{

}



MatrixXd Model::getGlobalStiffnessMatrix()
{
    unsigned int totalDOFNumber = getTotalFreeDOFNumber();
//    unsigned totalDOFNumber = getTotalDOFNumber();
    std::cout << "total DOF number: " << totalDOFNumber << endl;
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

VectorXd Model::getGlobalForceVector()
{
    //Itera pelos nós, para cada nó encontra a posição dele no force vector e coloca seus dofs no vetor
    VectorXd f = VectorXd::Zero(getTotalFreeDOFNumber());
    for (Load*& load : loads) {
        if (load->getType() == LoadType::NODE_LOAD) {
            VectorDOFLoad *vload = static_cast<VectorDOFLoad*>(load);

            VectorDOF *vdof = vload->getVdof();
            for (unsigned i = 0; i < vdof->getTotalDOFNumber(); i++) {
                if (vdof->getRestrictions()[i] == RestrictionTypes::FREE) {
                    f(vdof->getEquationNumber(i)) = vload->getValue(i);
                }
            }
        }
    }
    return f;
}

void Model::draw()
{
    for (Node*& n : nodes){
        n->draw();
    }
    for (Element*& e : elements) {
        e->draw();
    }
}

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
    for (Load*& l : loads) {
        ss << l->printInfo();
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



