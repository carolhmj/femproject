#include "beamdistributedload.h"
#include "projectdefines.h"
#include "loadtype.h"

BeamDistributedLoad::BeamDistributedLoad()
{

}

BeamDistributedLoad::BeamDistributedLoad(LoadComponent _startComponents, double _startDistance, LoadComponent _endComponents, double _endDistance, BeamElement3D *applyElement) :
    startComponents(_startComponents),
    startDistance(_startDistance),
    endComponents(_endComponents),
    endDistance(_endDistance)
{
    element = applyElement;
}

//Por enquanto vou pensar só no eixo y

std::vector<DOFLoad *> BeamDistributedLoad::transformToNodalLoads()
{
    double L = element->getLength();

    //Get components in the y direction, calculate y direction
    double qi = startComponents.getValue(LoadType::FY),
           qf = endComponents.getValue(LoadType::FY),
           a  = startDistance,
           b  = endDistance;

    //Calculate reactions in left side
    double RA = -((8*b^4+2*a*b^3-2*a^2*b^2+2*a^3*b-2*a^4)*qf+(2*b^4-2*a*b^3+2*a^2*b^2-2*a^3*b-8*a^4)*qi+((17*a^3+a^2*b                +a*b^2-3*b^3)*qi+(3*a^3-a^2*b-a*b^2-17*b^3)*qf)*L+((-3*a^2+4*a*b-3*b^2)*qi+(3*a^2-4*a*b+3*b^2)*qf)*L^2+((-13*a-3*b)*qi+(3*b-7*a)*qf)*L^3+(7*qi+3*qf)*L^4)/(20*L^3);

    double MA = -((12*b^4+3*a*b^3-3*a^2*b^2+3*a^3*b-3*a^4)*qf+(3*b^4-3*a*b^3+3*a^2*b^2-3*a^3*b-12*a^4)*qi+((33*a^3+4*a^2*b-a*b^2-2*b^3)*qi+(7*a^3-4*a^2*b+a*b^2-18*b^3)*qf)*L+((-27*a^2+a*b-2*b^2)*qi+(-3*a^2-a*b+2*b^2)*qf)*L^2+((3*a-2*b)*qi+(2*b-3*a)*qf)*L^3+(3*qi+2*qf)*L^4)/(60*L^2);

    //Calculate reactions in right side
    double RB = -RA + (qi*qf)*(L-a-b)/2;

}

std::string BeamDistributedLoad::printInfo()
{
    stringstream ss;
    ss << "§§§§§§§§§ BEAM DISTRIBUTED LOAD §§§§§§§§§" << endl;
    ss << "application start distance: " << startDistance << endl;
    ss << "start components:\n"  << startComponents.printInfo();
    ss << "application end distance: " << endDistance << endl;
    ss << "end components:\n"  << endComponents.printInfo();
    return ss.str();
}

