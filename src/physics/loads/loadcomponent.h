#ifndef LOADCOMPONENT_H
#define LOADCOMPONENT_H

#include "loadtype.h"
#include <vector>
#include "projectdefines.h"

/*
 * This class represents the components of a force
 */

class LoadComponent
{
public:
    LoadComponent();
    //2D constructor
    LoadComponent(double fx, double fy, double mz);
    //3D constructor
    LoadComponent(double fx, double fy, double fz, double mx, double my, double mz);

    //Getters and setters
    double getValue(unsigned int i);
    double getValueByType(LoadType type);

    //Debug information
    std::string printInfo();

private:
    std::vector<double> values;
    std::vector<LoadType> types;
};

#endif // LOADCOMPONENT_H
