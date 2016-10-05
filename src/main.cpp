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
#include "physics/node.h"
#include "physics/vectordof.h"
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
    Node *n = new Node(v);
    std::cout << n->printInfo();
}
#endif
