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
#include <Eigen/Core>
#include <iostream>

int main(int argc, char *argv[])
{
    //Cria os valores (2 de posição e um de rotação)
    std::vector<VectorDOFType> types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FREE, RestrictionTypes::FREE};
    std::vector<int> equations = {-1,0,1};
    VectorXd values(3);
    values << 0.5,1.5,0;
    VectorDOF *v = new VectorDOF(values, types, restrictions, equations);
    Node *n = new Node(Vector3d(), v);

//    std::cout << n->printInfo();

    std::vector<VectorDOFType> types2 = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> restrictions2 = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
    std::vector<int> equations2 = {2,3,4};
    VectorXd values2(3);
    values2 << 0,1,0;
    VectorDOF *v2 = new VectorDOF(values2, types2, restrictions2, equations2);
    Node *n2 = new Node(Vector3d(1,1,1), v2);

    Section *s = new Section(0.5, 0.025);

    Material *m = new Material(1E11, 0.25, 7000);

    BeamElement2D *el = new BeamElement2D(n, n2, s, m);
    std::cout << el->printInfo();
}
#endif
