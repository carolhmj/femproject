#ifndef BEAMDISTRIBUTEDLOAD_H
#define BEAMDISTRIBUTEDLOAD_H

#include "loadcomponent.h"
#include "elementload.h"
#include "beamelement3d.h"
#include "nodeload.h"
#include <utility>

class BeamDistributedLoad : public ElementLoad
{
public:
    BeamDistributedLoad();
    BeamDistributedLoad(LoadComponent _startComponents, double _startDistance, LoadComponent _endComponents, double _endDistance, BeamElement3D *applyElement);

    std::pair<std::vector<ComponentAddPair>, std::vector<ComponentAddPair>> transformToNodalLoads() override;

    string printInfo() override;

private:

    LoadComponent startComponents;
    double startDistance;

    LoadComponent endComponents;
    double endDistance;

    BeamElement3D *element;
};

#endif // BEAMDISTRIBUTEDLOAD_H
