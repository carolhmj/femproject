#ifndef BEAMPONTUALLOAD_H
#define BEAMPONTUALLOAD_H

#include "loadcomponent.h"
#include "beamelement3d.h"
#include "elementload.h"
#include "nodeload.h"

//Classe que representa uma força pontual em uma viga
class BeamPontualLoad : public ElementLoad
{
public:
    BeamPontualLoad();
    //2D constructor
    BeamPontualLoad(double fx, double fy, double mz, double dist, BeamElement3D *applyElement);
    //3D constructor
    BeamPontualLoad(double fx, double fy, double fz, double mx, double my, double mz, double dist, BeamElement3D *applyElement);

    //Override
    std::pair<std::vector<ComponentAddPair>, std::vector<ComponentAddPair>> transformToNodalLoads() override;

    //Debug infromation
    string printInfo() override;

private:
    //Force components
    LoadComponent components;
    //Distance to force application point
    double distance;
    //Element in which the force is applied
    BeamElement3D *element;
};

#endif // BEAMPONTUALLOAD_H
