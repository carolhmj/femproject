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
#include "projectdefines.h"
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

    //Exemplo 2: http://media.cheggcdn.com/media%2F24b%2F24bda2dd-e3be-4fcd-81ae-668ea7deb4fd%2Fimage
    //A resolução será feita com um modelo com 4 nós e 3 elementos
    std::vector<VectorDOFType> e2n1types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e2n1restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e2n1equations = {-1,-1,0};
    VectorDOF *e2n1v = new VectorDOF(e2n1types, e2n1restrictions, e2n1equations);
    Node *e2n1 = new Node(Vector3d(0.0,0.0,0.0), e2n1v);

    std::vector<VectorDOFType> e2n2types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e2n2restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
    std::vector<int> e2n2equations = {1,2,3};
    VectorDOF *e2n2v = new VectorDOF(e2n2types, e2n2restrictions, e2n2equations);
    Node *e2n2 = new Node(Vector3d(4.0,0.0,0.0), e2n2v);

    std::vector<VectorDOFType> e2n3types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e2n3restrictions = {RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e2n3equations = {4,-1,5};
    VectorDOF *e2n3v = new VectorDOF(e2n3types, e2n3restrictions, e2n3equations);
    Node *e2n3 = new Node(Vector3d(10.0,0.0,0.0), e2n3v);

    std::vector<VectorDOFType> e2n4types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e2n4restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
    std::vector<int> e2n4equations = {6,7,8};
    VectorDOF *e2n4v = new VectorDOF(e2n4types, e2n4restrictions, e2n4equations);
    Node *e2n4 = new Node(Vector3d(13.0,0.0,0.0), e2n4v);
    vector<Node*> e2nvector = {e2n1, e2n2, e2n3, e2n4};

    //Na questão temos que EI é constante e igual a 1750, logo vou colocar valores fictícios?
    Section *e2s = new Section(0.0, 1, 1);
    Material *e2m = new Material(1750, 0.0, 0.0);

    BeamElement2D *e2b1 = new BeamElement2D(e2n1, e2n2, e2s, e2m);
    BeamElement2D *e2b2 = new BeamElement2D(e2n2, e2n3, e2s, e2m);
    BeamElement2D *e2b3 = new BeamElement2D(e2n3, e2n4, e2s, e2m);
    vector<Element*> e2bvector = {e2b1, e2b2, e2b3};

    //Loads
    VectorXd e2n2lvalues(3);
    e2n2lvalues << 0,-5,0;
    VectorDOFLoad *e2n2load = new VectorDOFLoad(e2n2v, e2n2lvalues);
    VectorXd e2n4lvalues(3);
    e2n4lvalues << 0,-3,0;
    VectorDOFLoad *e2n4load = new VectorDOFLoad(e2n4v, e2n4lvalues);
    vector<Load*> e2lvector = {e2n2load, e2n4load};

    Model *m2 = new Model("Simple Beam 2D Test 2", e2nvector, e2bvector, e2lvector);
    std::cout << m2->printInfo();

    MatrixXd e2globalMatrix = m2->getGlobalStiffnessMatrix();
    std::cout << "Global stiffness matrix: " << endl << e2globalMatrix << endl;

    VectorXd e2forceVector = m2->getGlobalForceVector();
    std::cout << "Global force  vector: " << endl << e2forceVector << endl;

    FullPivHouseholderQR<MatrixXd> e2solver(e2globalMatrix);
    VectorXd e2displacementVector = e2solver.solve(e2forceVector);
    std::cout << "Result: " << endl << e2displacementVector << endl;


    //Exemplo 3: Cantilever Beam de L=10m e A=0.05m2 e E=10GPa submetido a uma força de 200N na extremidade
    std::vector<VectorDOFType> e3n1types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e3n1restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED};
    std::vector<int> e3n1equations = {-1,-1,-1};
    VectorDOF *e3n1v = new VectorDOF(e3n1types, e3n1restrictions, e3n1equations);
    Node *e3n1 = new Node(Vector3d(0.0,0.0,0.0), e3n1v);

    std::vector<VectorDOFType> e3n2types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e3n2restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
    std::vector<int> e3n2equations = {0,1,2};
    VectorDOF *e3n2v = new VectorDOF(e3n2types, e3n2restrictions, e3n2equations);
    Node *e3n2 = new Node(Vector3d(10.0,0.0,0.0), e3n2v);
    vector<Node*> e3nvec = {e3n1,e3n2};

    Section *e3s = new Section(0.0,0.0,0.05);
    Material *e3m = new Material(10E9,0.0,0.0);

    BeamElement2D *e3b1 = new BeamElement2D(e3n1,e3n2,e3s,e3m);
    vector<Element*> e3elvec = {e3b1};

    VectorXd e3l1val(3);
    e3l1val << 200, 0, 0;
    VectorDOFLoad *e3n2load = new VectorDOFLoad(e3n2v, e3l1val);
    vector<Load*> e3lvec = {e3n2load};

    Model *m3 = new Model("Cantilever Beam Test 3", e3nvec, e3elvec, e3lvec);
    std::cout << m3->printInfo();

    MatrixXd e3globalMatrix = m3->getGlobalStiffnessMatrix();
    std::cout << "Global stiffness matrix: " << endl << e3globalMatrix << endl;

    VectorXd e3forceVector = m3->getGlobalForceVector();
    std::cout << "Global force  vector: " << endl << e3forceVector << endl;

    FullPivHouseholderQR<MatrixXd> e3solver(e3globalMatrix);
    VectorXd e3displacementVector = e3solver.solve(e3forceVector);
    std::cout << "Result: " << endl << e3displacementVector << endl;
}
#endif
