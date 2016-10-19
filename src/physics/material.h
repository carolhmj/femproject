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
    Material(double _youngModulus, double _poissonCoefficient, double _density);
    string printInfo();
    double getYoungModulus() const;

    double getPoissonCoefficient() const;

    double getDensity() const;

private:
    double youngModulus;
    double poissonCoefficient;
    double density;
};

#endif // MATERIAL_H
