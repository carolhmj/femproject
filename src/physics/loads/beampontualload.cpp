#include "beampontualload.h"
#include "projectdefines.h"
#include <sstream>

#include <sstream>

BeamPontualLoad::BeamPontualLoad()
{

}

BeamPontualLoad::BeamPontualLoad(double fx, double fy, double mz, double dist, BeamElement3D *applyElement)
{
    components = LoadComponent(fx,fy,mz);
    distance = dist;
    element = applyElement;
}

BeamPontualLoad::BeamPontualLoad(double fx, double fy, double fz, double mx, double my, double mz, double dist, BeamElement3D *applyElement)
{
    components = LoadComponent(fx,fy,fz,mx,my,mz);
    distance = dist;
    element = applyElement;
}

std::pair<std::vector<ComponentAddPair>, std::vector<ComponentAddPair> > BeamPontualLoad::transformToNodalLoads()
{

}

std::string BeamPontualLoad::printInfo()
{
    std::stringstream ss;
    ss << "§§§§§§§§§ BEAM PONTUAL LOAD §§§§§§§§§" << endl;
    ss << "application distance: " << distance << endl;
    ss << components.printInfo();
    return ss.str();
}

Element *BeamPontualLoad::getElement()
{
    return element;
}

