#include "beamdistributedload.h"
#include "projectdefines.h"
#include "loadtype.h"
#include <cmath>

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

std::pair<std::vector<ComponentAddPair>, std::vector<ComponentAddPair> > BeamDistributedLoad::transformToNodalLoads()
{
    double L = element->getLength();

    //Get components in the y direction, calculate y direction
    double qi = startComponents.getValueByType(LoadType::FY),
           qf = endComponents.getValueByType(LoadType::FY),
           a  = startDistance,
           b  = endDistance;

    using std::pow;

    //Calculate reactions in left side
    double RA = -((8*pow(b,4)+2*a*pow(b,3)-2*pow(a,2)*pow(b,2)+2*pow(a,3)*b-2*pow(a,4))*qf+(2*pow(b,4)-2*a*pow(b,3)+2*pow(a,2)*pow(b,2)-2*pow(a,3)*b-8*pow(a,4))*qi+((17*pow(a,3)+pow(a,2)*b                +a*pow(b,2)-3*pow(b,3))*qi+(3*pow(a,3)-pow(a,2)*b-a*pow(b,2)-17*pow(b,3))*qf)*L+((-3*pow(a,2)+4*a*b-3*pow(b,2))*qi+(3*pow(a,2)-4*a*b+3*pow(b,2))*qf)*pow(L,2)+((-13*a-3*b)*qi+(3*b-7*a)*qf)*pow(L,3)+(7*qi+3*qf)*pow(L,4))/(20*pow(L,3));

    double MA = -((12*pow(b,4)+3*a*pow(b,3)-3*pow(a,2)*pow(b,2)+3*pow(a,3)*b-3*pow(a,4))*qf+(3*pow(b,4)-3*a*pow(b,3)+3*pow(a,2)*pow(b,2)-3*pow(a,3)*b-12*pow(a,4))*qi+((33*pow(a,3)+4*pow(a,2)*b-a*pow(b,2)-2*pow(b,3))*qi+(7*pow(a,3)-4*pow(a,2)*b+a*pow(b,2)-18*pow(b,3))*qf)*L+((-27*pow(a,2)+a*b-2*pow(b,2))*qi+(-3*pow(a,2)-a*b+2*pow(b,2))*qf)*pow(L,2)+((3*a-2*b)*qi+(2*b-3*a)*qf)*pow(L,3)+(3*qi+2*qf)*pow(L,4))/(60*pow(L,2));

    //Calculate force reactions in right side
    double RB = -RA + (qi*qf)*(L-a-b)/2;
    //Due to our signal convention, invert RB sign
    RB = -RB;

    //Calculate moment reactions in right side
    double MB = ((-2*pow(b,2)-a*b+pow(a,2))*qf+(-pow(b,2)+a*b+2*pow(a,2))*qi+6*MA-6*
                RA+((-4*a-b)*qi+(b-2*a)*qf)*L+(2*qi+qf)*pow(L,2))/6;

    //Create the nodal load
    std::vector<ComponentAddPair> n1add = {ComponentAddPair(RA, LoadType::FY), ComponentAddPair(MA, LoadType::MZ)};
    std::vector<ComponentAddPair> n2add = {ComponentAddPair(RB, LoadType::FY), ComponentAddPair(MB, LoadType::MZ)};
    std::pair<std::vector<ComponentAddPair>, std::vector<ComponentAddPair>> p(n1add, n2add);
    return p;
}

void BeamDistributedLoad::draw(QOpenGLShaderProgram *program)
{

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

Element *BeamDistributedLoad::getElement()
{
    return element;
}
