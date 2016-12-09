#ifndef LOADCOMPONENT_H
#define LOADCOMPONENT_H

#include "loadtype.h"
#include <vector>
#include "projectdefines.h"

/*
 * Essa classe representa um componente de uma força.
 */

class LoadComponent
{
public:
    LoadComponent();
    //2D constructor
    LoadComponent(double fx, double fy, double mz);
    //3D constructor
    LoadComponent(double fx, double fy, double fz, double mx, double my, double mz);


    double getValue(unsigned int i);

    std::string printInfo();
private:
    std::vector<double> values;
    std::vector<LoadComponentType> types;
};

#endif // LOADCOMPONENT_H
