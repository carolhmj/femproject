#ifndef BEAMPONTUALLOAD_H
#define BEAMPONTUALLOAD_H

#include "loadcomponent.h"

//Classe que representa uma força pontual em uma viga
class BeamPontualLoad : public ElementLoad
{
public:
    BeamPontualLoad();
    //2D constructor
    BeamPontualLoad(double fx, double fy, double mz, double dist);
    //3D constructor
    BeamPontualLoad(double fx, double fy, double fz, double mx, double my, double mz, double dist);
    string printInfo() override;

private:
    LoadComponent components;
    //Distance to force application point
    double applyDistance;
};

#endif // BEAMPONTUALLOAD_H
