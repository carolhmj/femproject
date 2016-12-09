#include "beampontualload.h"
#include "projectdefines.h"

BeamPontualLoad::BeamPontualLoad()
{

}

BeamPontualLoad::BeamPontualLoad(double fx, double fy, double mz, double dist)
{
    components = LoadComponent(fx,fy,fz);
    applyDistance = dist;
}

BeamPontualLoad::BeamPontualLoad(double fx, double fy, double fz, double mx, double my, double mz, double dist)
{
    components = LoadComponent(fx,fy,fz,mx,my,mz);
    applyDistance = dist;
}

std::string BeamPontualLoad::printInfo()
{
    stringstream ss;
    ss << "§§§§§§§§§ BEAM PONTUAL LOAD §§§§§§§§§" << endl;
    ss << "application distance: " << applyDistance << endl;
    ss << components.printInfo();
    return ss.str();
}

