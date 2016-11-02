#if USE_INTERFACE
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
#endif

#if !USE_INTERFACE
#include "node.h"
#include "vectordof.h"
#include "beamelement2d.h"
#include "vectordofload.h"
#include "model.h"
#include <Eigen/Core>
#include <Eigen/QR>
#include <iostream>

int main(int argc, char *argv[])
{
    //Exemplo 1: http://what-when-how.com/the-finite-element-method/fem-for-beams-finite-element-method-part-2/

    //Cria os valores (2 de posição e um de rotação)
    std::vector<VectorDOFType> types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED};
    std::vector<int> equations = {-1,-1,-1};
    VectorDOF *v = new VectorDOF(types, restrictions, equations);
    Node *n = new Node(Vector3d(0.0,0.0,0.0), v);

    std::vector<VectorDOFType> types2 = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> restrictions2 = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
    std::vector<int> equations2 = {0,1,2};
    VectorDOF *v2 = new VectorDOF(types2, restrictions2, equations2);
    Node *n2 = new Node(Vector3d(0.5,0,0), v2);

    //Seção largura 0.1 e altura 0.06
    Section *s = new Section(0.0, 1.8E-6, 0.006);

    //Material alumínio
    Material *m = new Material(69E9, 0.0, 0.33, 0.0);

    BeamElement2D *el = new BeamElement2D(n, n2, Vector3d(0,1,0), s, m);
    vector<Node*> nvec = {n, n2};
    vector<Element*> elvec = {el};

    VectorXd valuesLoad(3);
    valuesLoad << 0, -1000, 0;
    //Força agindo no segundo nó
    VectorDOFLoad *load = new VectorDOFLoad(v2, valuesLoad);
    vector<Load*> lvec = {load};

    Model *md = new Model("Cantilever beam 2D Test 1", nvec, elvec, lvec);
    std::cout << md->printInfo();

    MatrixXd globalMatrix = md->getGlobalStiffnessMatrix();
    std::cout << "Global stiffness matrix: " << endl << globalMatrix << endl;

    VectorXd forceVector = md->getGlobalForceVector();
    std::cout << "Global force  vector: " << endl << forceVector << endl;

    FullPivHouseholderQR<MatrixXd> solver(globalMatrix);
    VectorXd displacementVector = solver.solve(forceVector);
    std::cout << "Result: " << endl << displacementVector << endl;

}
#endif
