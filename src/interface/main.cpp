#if USE_INTERFACE
#include "mainwindow.h"
#include "glwidget.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);

    QApplication a(argc, argv);

    MainWindow w;
    GLWidget* canvas = w.findChild<GLWidget*>("canvas");
    canvas->setFormat(format);
    w.show();

    return a.exec();
}
#endif

#if !USE_INTERFACE
#include "node.h"
#include "vectordof.h"
#include "beamelement2d.h"
#include "beamelement3d.h"
#include "model.h"
#include "projectdefines.h"
#include <Eigen/Core>
#include <Eigen/QR>
#include <iostream>
#include <iomanip>

int main(int argc, char *argv[])
{
    //Exemplo 1: http://what-when-how.com/the-finite-element-method/fem-for-beams-finite-element-method-part-2/

    //Cria os valores (2 de posição e um de rotação)
//    std::vector<VectorDOFType> types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED};
//    std::vector<int> equations = {-1,-1,-1};
//    VectorDOF *v = new VectorDOF(types, restrictions, equations);
//    Node *n = new Node(Vector3d(0.0,0.0,0.0), v);

//    std::vector<VectorDOFType> types2 = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> restrictions2 = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
//    std::vector<int> equations2 = {0,1,2};
//    VectorDOF *v2 = new VectorDOF(types2, restrictions2, equations2);
//    Node *n2 = new Node(Vector3d(0.5,0,0), v2);

//    //Seção largura 0.1 e altura 0.06
//    Section *s = new Section(0.0, 1.8E-6, 0.0, 0.006);

//    //Material alumínio
//    Material *m = new Material(69E9, 0.0, 0.33, 0.0);

//    BeamElement2D *el = new BeamElement2D(n, n2, Vector3d(0,1,0), s, m);
//    vector<Node*> nvec = {n, n2};
//    vector<Element*> elvec = {el};

//    VectorXd valuesLoad(3);
//    valuesLoad << 0, -1000, 0;

//    //Força agindo no segundo nó
//    VectorDOFLoad *load = new VectorDOFLoad(v2, valuesLoad);
//    vector<Load*> lvec = {load};

//    Model *md = new Model("Cantilever beam 2D Test 1", nvec, elvec, lvec);
//    std::cout << md->printInfo();

//    MatrixXd globalMatrix = md->getGlobalStiffnessMatrix();
//    std::cout << "Global stiffness matrix: " << endl << globalMatrix << endl;

//    VectorXd forceVector = md->getGlobalForceVector();
//    std::cout << "Global force  vector: " << endl << forceVector << endl;

//    FullPivHouseholderQR<MatrixXd> solver(globalMatrix);
//    VectorXd displacementVector = solver.solve(forceVector);
//    std::cout << "Result: " << endl << displacementVector << endl;


//    //Exemplo 1.2: http://what-when-how.com/the-finite-element-method/fem-for-beams-finite-element-method-part-2/

////    Cria os valores (2 de posição e um de rotação)
//    std::vector<VectorDOFType> ttypes = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> trestrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED};
//    std::vector<int> tequations = {-1,-1,-1, -1, -1, -1};
//    VectorDOF *tv = new VectorDOF(ttypes, trestrictions, tequations);
//    Node *tn = new Node(Vector3d(0.0,0.0,0.0), tv);

//    std::vector<VectorDOFType> ttypes2 = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> trestrictions2 = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
//    std::vector<int> tequations2 = {0,1,2,3,4,5};
//    VectorDOF *tv2 = new VectorDOF(ttypes2,trestrictions2, tequations2);
//    Node *tn2 = new Node(Vector3d(0.5,0,0), tv2);

//    //Seção largura 0.1 e altura 0.06
//    Section *ts = new Section(0.0, 1.8E-6, 0.0, 0.006);

//    //Material alumínio
//    Material *tm = new Material(69E9, 0.0, 0.33, 0.0);

//    BeamElement3D *tel = new BeamElement3D(tn, tn2, Vector3d(0,2,0), ts, tm);
//    vector<Node*> tnvec = {tn, tn2};
//    vector<Element*> telvec = {tel};

//    VectorXd tvaluesLoad(6);
//    tvaluesLoad << 0, -1000, 0, 0, 0, 0;
//    //Força agindo no segundo nó
//    VectorDOFLoad *tload = new VectorDOFLoad(tv2, tvaluesLoad);
//    vector<Load*> tlvec = {tload};

//    Model *tmd = new Model("Cantilever beam 2D Test 1", tnvec, telvec, tlvec);
//    std::cout << tmd->printInfo();

//    MatrixXd tglobalMatrix = tmd->getGlobalStiffnessMatrix();
//    std::cout << "Global stiffness matrix: " << endl << tglobalMatrix << endl;

//    VectorXd tforceVector = tmd->getGlobalForceVector();
//    std::cout << "Global force  vector: " << endl << tforceVector << endl;

//    FullPivHouseholderQR<MatrixXd> tsolver(tglobalMatrix);
//    VectorXd tdisplacementVector = tsolver.solve(tforceVector);
//    std::cout << "Result: " << endl << tdisplacementVector << endl;

    //Exemplo 2: http://media.cheggcdn.com/media%2F24b%2F24bda2dd-e3be-4fcd-81ae-668ea7deb4fd%2Fimage
    //A resolução será feita com um modelo com 4 nós e 3 elementos
//    std::vector<VectorDOFType> e2n1types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e2n1restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
//    std::vector<int> e2n1equations = {-1,-1,0};
//    VectorDOF *e2n1v = new VectorDOF(e2n1types, e2n1restrictions, e2n1equations);
//    Node *e2n1 = new Node(Vector3d(0.0,0.0,0.0), e2n1v);

//    std::vector<VectorDOFType> e2n2types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e2n2restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
//    std::vector<int> e2n2equations = {1,2,3};
//    VectorDOF *e2n2v = new VectorDOF(e8n2types, e8n2restrictions, e8n2equations);
//    Node *e8n2 = new Node(Vector3d(4.0,0.0,0.0), e8n2v);

//    std::vector<VectorDOFType> e8n3types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e8n3restrictions = {RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FREE};
//    std::vector<int> e8n3equations = {4,-1,5};
//    VectorDOF *e8n3v = new VectorDOF(e8n3types, e8n3restrictions, e8n3equations);
//    Node *e8n3 = new Node(Vector3d(10.0,0.0,0.0), e8n3v);

//    std::vector<VectorDOFType> e8n4types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e8n4restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
//    std::vector<int> e8n4equations = {6,7,8};
//    VectorDOF *e8n4v = new VectorDOF(e8n4types, e8n4restrictions, e8n4equations);
//    Node *e8n4 = new Node(Vector3d(13.0,0.0,0.0), e8n4v);
//    vector<Node*> e8nvector = {e8n1, e8n2, e8n3, e8n4};

//    //Na questão temos que EI é constante e igual a 1750, logo vou colocar valores fictícios?
//    Section *e8s = new Section(0.0, 1, 1);
//    Material *e8m = new Material(1750, 0.0, 0.0, 0.0);

//    BeamElement2D *e8b1 = new BeamElement2D(e8n1, e8n2, Vector3d(0,1,0),  e8s, e8m);
//    BeamElement2D *e8b2 = new BeamElement2D(e8n2, e8n3, Vector3d(0,1,0),  e8s, e8m);
//    BeamElement2D *e8b3 = new BeamElement2D(e8n3, e8n4, Vector3d(0,1,0),  e8s, e8m);
//    vector<Element*> e8bvector = {e8b1, e8b2, e8b3};

//    //Loads
//    VectorXd e8n2lvalues(3);
//    e8n2lvalues << 0,-5,0;
//    VectorDOFLoad *e8n2load = new VectorDOFLoad(e8n2v, e8n2lvalues);
//    VectorXd e8n4lvalues(3);
//    e8n4lvalues << 0,-3,0;
//    VectorDOFLoad *e8n4load = new VectorDOFLoad(e8n4v, e8n4lvalues);
//    vector<Load*> e8lvector = {e8n2load, e8n4load};

//    Model *m2 = new Model("Simple Beam 2D Test 2", e8nvector, e8bvector, e8lvector);
//    std::cout << m2->printInfo();

//    MatrixXd e8globalMatrix = m2->getGlobalStiffnessMatrix();
//    std::cout << "Global stiffness matrix: " << endl << e8globalMatrix << endl;

//    VectorXd e8forceVector = m2->getGlobalForceVector();
//    std::cout << "Global force  vector: " << endl << e8forceVector << endl;

//    FullPivHouseholderQR<MatrixXd> e8solver(e8globalMatrix);
//    VectorXd e8displacementVector = e8solver.solve(e8forceVector);
//    std::cout << "Result: " << endl << e8displacementVector << endl;


//    //Exemplo 3: Cantilever Beam de L=10m e A=0.05m2 e E=10GPa submetido a uma força de 200N na extremidade
//    std::vector<VectorDOFType> e3n1types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e3n1restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED};
//    std::vector<int> e3n1equations = {-1,-1,-1};
//    VectorDOF *e3n1v = new VectorDOF(e3n1types, e3n1restrictions, e3n1equations);
//    Node *e3n1 = new Node(Vector3d(0.0,0.0,0.0), e3n1v);

//    std::vector<VectorDOFType> e3n2types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e3n2restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
//    std::vector<int> e3n2equations = {0,1,2};
//    VectorDOF *e3n2v = new VectorDOF(e3n2types, e3n2restrictions, e3n2equations);
//    Node *e3n2 = new Node(Vector3d(10.0,0.0,0.0), e3n2v);
//    vector<Node*> e3nvec = {e3n1,e3n2};

//    Section *e3s = new Section(0.0,0.0,0.05);
//    Material *e3m = new Material(10E9,0.0, 0.0,0.0);

//    BeamElement2D *e3b1 = new BeamElement2D(e3n1,e3n2, Vector3d(0,1,0), e3s,e3m);
//    vector<Element*> e3elvec = {e3b1};

//    VectorXd e3l1val(3);
//    e3l1val << 200, 0, 0;
//    VectorDOFLoad *e3n2load = new VectorDOFLoad(e3n2v, e3l1val);
//    vector<Load*> e3lvec = {e3n2load};

//    Model *m3 = new Model("Cantilever Beam Test 3", e3nvec, e3elvec, e3lvec);
//    std::cout << m3->printInfo();

//    MatrixXd e3globalMatrix = m3->getGlobalStiffnessMatrix();
//    std::cout << "Global stiffness matrix: " << endl << e3globalMatrix << endl;

//    VectorXd e3forceVector = m3->getGlobalForceVector();
//    std::cout << "Global force  vector: " << endl << e3forceVector << endl;

//    FullPivHouseholderQR<MatrixXd> e3solver(e3globalMatrix);
//    VectorXd e3displacementVector = e3solver.solve(e3forceVector);
//    std::cout << "Result: " << endl << e3displacementVector << endl;

    //Exemplo 4: https://www.kth.se/polopoly_fs/1.251918!/Menu/general/column-content/attachment/Examples_HT2011.pdf
    //Questão 1.2
//    std::vector<VectorDOFType> e4n1types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e4n1restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED};
//    std::vector<int> e4n1equations = {-1,-1,-1,-1,-1,-1};
//    VectorDOF *e4n1v = new VectorDOF(e4n1types, e4n1restrictions, e4n1equations);
//    Node *e4n1 = new Node(Vector3d(0.0,1.0,0.0), e4n1v);

//    std::vector<VectorDOFType> e4n2types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e4n2restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
//    std::vector<int> e4n2equations = {0,1,-1,-1,-1,2};
//    VectorDOF *e4n2v = new VectorDOF(e4n2types, e4n2restrictions, e4n2equations);
//    Node *e4n2 = new Node(Vector3d(1.0,0.0,0.0), e4n2v);

//    std::vector<VectorDOFType> e4n3types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e4n3restrictions = {{RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE}};
//    std::vector<int> e4n3equations = {3,4,-1,-1,-1,5};
//    VectorDOF *e4n3v = new VectorDOF(e4n3types, e4n3restrictions, e4n3equations);
//    Node *e4n3 = new Node(Vector3d(2.0,1.0,0.0), e4n3v);
//    vector<Node*> e4nvec = {e4n1, e4n2, e4n3};

//    Section *e4s = new Section(1E-6,1E-6,1E-6,1E-5);
//    Material *e4m = new Material(1E9,1E9,0.5,1E9);
//    BeamElement3D *e4b1 = new BeamElement3D(e4n1,e4n2, Vector3d(0,10,0), e4s,e4m);
//    BeamElement3D *e4b2 = new BeamElement3D(e4n2,e4n3, Vector3d(0,10,0), e4s, e4m);
//    vector<Element*> e4elvec = {e4b1, e4b2};

//    VectorXd e4l1val(6);
//    e4l1val << 10, 0, 0, 0, 0, 0;
//    VectorDOFLoad *e4n3load = new VectorDOFLoad(e4n3v, e4l1val);
//    vector<Load*> e4lvec = {e4n3load};

//    Model *m4 = new Model("Inclined bar test 4", e4nvec, e4elvec, e4lvec);
//    std::cout << m4->printInfo();

//    MatrixXd e4globalMatrix = m4->getGlobalStiffnessMatrix();
//    std::cout << "Global stiffness matrix: " << endl << e4globalMatrix << endl;

//    VectorXd e4forceVector = m4->getGlobalForceVector();
//    std::cout << "Global force vector: " << endl << e4forceVector << endl;

//    FullPivHouseholderQR<MatrixXd> e4solver(e4globalMatrix);
//    VectorXd e4displacementVector = e4solver.solve(e4forceVector);
//    std::cout << "Result: " << endl << e4displacementVector << endl;

//    //Exemplo 6: No caderno
//    std::vector<VectorDOFType> e6n1types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e6n1restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED};
//    std::vector<int> e6n1equations = {-1,-1,-1,-1,-1,-1};
//    VectorDOF *e6n1v = new VectorDOF(e6n1types, e6n1restrictions, e6n1equations);
//    Node *e6n1 = new Node(Vector3d(0.0,0.0,0.0), e6n1v);

//    std::vector<VectorDOFType> e6n2types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e6n2restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FREE};
//    std::vector<int> e6n2equations = {0,1,2,3,4,5};
//    VectorDOF *e6n2v = new VectorDOF(e6n2types, e6n2restrictions, e6n2equations);
//    Node *e6n2 = new Node(Vector3d(1.0,1.0,0.0), e6n2v);

//    vector<Node*> e6nvec = {e6n1, e6n2};

//    Section *e6s = new Section(1E-6,1E-6,1E-6,1E-5);
//    Material *e6m = new Material(1E9,1E9,0.5,1E9);

//    BeamElement3D *e6b1 = new BeamElement3D(e6n1,e6n2, Vector3d(0,10,0), e6s, e6m);
//    vector<Element*> e6elvec = {e6b1};

//    VectorXd e6l1val(6);
//    e6l1val << 0, -10, 0, 0, 0, 0;
//    VectorDOFLoad *e6n2load = new VectorDOFLoad(e6n2v, e6l1val);
//    vector<Load*> e6lvec = {e6n2load};

//    Model *m6 = new Model("Inclined bar test 6", e6nvec, e6elvec, e6lvec);
//    std::cout << m6->printInfo();

//    MatrixXd e6globalMatrix = m6->getGlobalStiffnessMatrix();
//    std::cout << "Global stiffness matrix: " << endl << e6globalMatrix << endl;

//    VectorXd e6forceVector = m6->getGlobalForceVector();
//    std::cout << "Global force vector: " << endl << e6forceVector << endl;

//    FullPivHouseholderQR<MatrixXd> e6solver(e6globalMatrix);
//    VectorXd e6displacementVector = e6solver.solve(e6forceVector);
//    std::cout << "Result: " << endl << e6displacementVector << endl;

//    //Exemplo 7: https://www.clear.rice.edu/mech400/Castigliano_examples.pdf
//    //Questão 12-13
//    std::vector<VectorDOFType> e7n1types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e7n1restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED};
//    std::vector<int> e7n1equations = {-1,-1,-1,-1,-1,-1};
//    VectorDOF *e7n1v = new VectorDOF(e7n1types, e7n1restrictions, e7n1equations);
//    Node *e7n1 = new Node(Vector3d(0.0,1.0,0.0), e7n1v);

//    //Mudando pra ficar fixo no plano xy
//    std::vector<VectorDOFType> e7n2types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e7n2restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
//    std::vector<int> e7n2equations = {0,1,-1,-1,-1,2};
//    VectorDOF *e7n2v = new VectorDOF(e7n2types, e7n2restrictions, e7n2equations);
//    Node *e7n2 = new Node(Vector3d(4.0,1.0,0.0), e7n2v);


//    std::vector<VectorDOFType> e7n3types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
//    std::vector<RestrictionTypes> e7n3restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
//    std::vector<int> e7n3equations = {3,4,-1,-1,-1,5};
//    VectorDOF *e7n3v = new VectorDOF(e7n3types, e7n3restrictions, e7n3equations);
//    Node *e7n3 = new Node(Vector3d(4.0,0.0,0.0), e7n3v);

//    vector<Node*> e7nvec = {e7n1, e7n2, e7n3};

//    Section *e7s = new Section(1E-6,1E-6,1E-6,1E-5);
//    Material *e7m = new Material(1E9,1E9,0.5,1E9);
//    BeamElement3D *e7b1 = new BeamElement3D(e7n1,e7n2, Vector3d(0,10,0), e7s,e7m);
//    BeamElement3D *e7b2 = new BeamElement3D(e7n2,e7n3, Vector3d(10,0,0), e7s, e7m);
//    vector<Element*> e7elvec = {e7b1, e7b2};

//    VectorXd e7l1val(6);
//    e7l1val << 10, 0, 0, 0, 0, 0;
//    VectorDOFLoad *e7n3load = new VectorDOFLoad(e7n3v, e7l1val);
//    vector<Load*> e7lvec = {e7n3load};

//    Model *m7 = new Model("2-element bar test 7", e7nvec, e7elvec, e7lvec);
//    std::cout << m7->printInfo();

//    MatrixXd e7globalMatrix = m7->getGlobalStiffnessMatrix();
//    std::cout << "Global stiffness matrix: " << endl << e7globalMatrix << endl;

//    VectorXd e7forceVector = m7->getGlobalForceVector();
//    std::cout << "Global force vector: " << endl << e7forceVector << endl;

//    FullPivHouseholderQR<MatrixXd> e7solver(e7globalMatrix);
//    VectorXd e7displacementVector = e7solver.solve(e7forceVector);
//    std::cout << "Result: " << endl << e7displacementVector << endl;


//    Exemplo 8 (Exemplo 2 com elementos 3D, MODIFICADO): http://media.cheggcdn.com/media%2F24b%2F24bda2dd-e3be-4fcd-81ae-668ea7deb4fd%2Fimage
    //A resolução será feita com um modelo com 4 nós e 3 elementos
    std::vector<VectorDOFType> e8n1types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e8n1restrictions = {RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e8n1equations = {-1,-1,-1,-1,-1,0};
    VectorDOF *e8n1v = new VectorDOF(e8n1types, e8n1restrictions, e8n1equations);
    Node *e8n1 = new Node(Vector3d(0.0,0.0,0.0), e8n1v);

    std::vector<VectorDOFType> e8n2types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e8n2restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e8n2equations = {1,2,-1,-1,-1,3};
    VectorDOF *e8n2v = new VectorDOF(e8n2types, e8n2restrictions, e8n2equations);
    Node *e8n2 = new Node(Vector3d(4.0,0.0,0.0), e8n2v);

    std::vector<VectorDOFType> e8n3types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e8n3restrictions = {RestrictionTypes::FREE, RestrictionTypes::FIXED,  RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e8n3equations = {4,-1,-1,-1,-1,5};
    VectorDOF *e8n3v = new VectorDOF(e8n3types, e8n3restrictions, e8n3equations);
    Node *e8n3 = new Node(Vector3d(10.0,0.0,0.0), e8n3v);

    std::vector<VectorDOFType> e8n4types = {VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::TRANSLATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION, VectorDOFType::ROTATION};
    std::vector<RestrictionTypes> e8n4restrictions = {RestrictionTypes::FREE, RestrictionTypes::FREE, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FIXED, RestrictionTypes::FREE};
    std::vector<int> e8n4equations = {6,7,-1,-1,-1,8};
    VectorDOF *e8n4v = new VectorDOF(e8n4types, e8n4restrictions, e8n4equations);
    Node *e8n4 = new Node(Vector3d(13.0,0.0,0.0), e8n4v);
    vector<Node*> e8nvector = {e8n1, e8n2, e8n3, e8n4};

    //I = 0.036m^-4, A = 0.12m^2
    Section *e8s = new Section(0, 0.0036, 0, 0.12);
    //Material: Concreto http://www.concrete.org.uk/fingertips-nuggets.asp?cmd=display&id=525
    Material *e8m = new Material(10E9, 0, 0, 10);

    BeamElement3D *e8b1 = new BeamElement3D(e8n1, e8n2, Vector3d(0,1,0),  e8s, e8m);
    BeamElement3D *e8b2 = new BeamElement3D(e8n2, e8n3, Vector3d(0,1,0),  e8s, e8m);
    BeamElement3D *e8b3 = new BeamElement3D(e8n3, e8n4, Vector3d(0,1,0),  e8s, e8m);
    vector<Element*> e8bvector = {e8b1, e8b2, e8b3};

    //Loads
    //Força no nó 2 é de 5000N
//    VectorXd e8n2lvalues(6);
//    e8n2lvalues << 0,-5000,0,0,0,0;
//    VectorDOFLoad *e8n2load = new VectorDOFLoad(e8n2v, e8n2lvalues);
    NodeLoad *e8n2load = new NodeLoad(0.0,-5000.0,0.0,0.0,0.0,0.0, e8n2);
    //Força no nó 4 é de 3000N
//    VectorXd e8n4lvalues(6);
//    e8n4lvalues << 0,-3000,0,0,0,0;
//    VectorDOFLoad *e8n4load = new VectorDOFLoad(e8n4v, e8n4lvalues);
    NodeLoad* e8n4load = new NodeLoad(0.0,-3000.0,0.0,0.0,0.0,0.0, e8n4);
//    vector<Load*> e8lvector = {e8n2load, e8n4load};

    vector<NodeLoad*> e8lvector = {e8n2load, e8n4load};
    vector<ElementLoad*> e8levector;

    Model *m8 = new Model("Simple Beam 3D Test 2", e8nvector, e8bvector, e8lvector, e8levector);
    std::cout << m8->printInfo();

    MatrixXd e8globalMatrix = m8->getGlobalStiffnessMatrix();
    std::cout << "Global stiffness matrix: " << endl << e8globalMatrix << endl;

    VectorXd e8forceVector = m8->getGlobalForceVector();
    std::cout << "Global force  vector: " << endl << e8forceVector << endl;

    MatrixXd e8MassMatrix = m8->getGlobalMassMatrix();
    std::cout << "Global mass matrix: " << endl << e8MassMatrix << endl;

    IOFormat HeavyFmt(FullPrecision, 0, ", ", "\n", "|", "|", "[", "]");
    std::cout.precision(8);
    FullPivHouseholderQR<MatrixXd> e8solver(e8globalMatrix);
    VectorXd e8displacementVector = e8solver.solve(e8forceVector);
    std::cout << "Result: " << endl << e8displacementVector.format(HeavyFmt) << endl;

    //NÃO USAR POISSON 0.5
}
#endif
