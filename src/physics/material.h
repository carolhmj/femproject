#ifndef MATERIAL_H
#define MATERIAL_H
#include <string>

using std::string;
//using std::endl;
//Classe que representa um material
class Material
{
public:
    Material();
    string printInfo();
private:
    double youngModulus;
    double poissonCoefficient;
    double density;
};

#endif // MATERIAL_H
