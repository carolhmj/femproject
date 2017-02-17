#ifndef BEAMDISTRIBUTEDLOAD_H
#define BEAMDISTRIBUTEDLOAD_H

#include "loadcomponent.h"
#include "elementload.h"
#include "beamelement3d.h"

class BeamDistributedLoad : public ElementLoad
{
public:
    BeamDistributedLoad();
    BeamDistributedLoad(LoadComponent _startComponents, double _startDistance, LoadComponent _endComponents, double _endDistance, BeamElement3D *applyElement);

    std::vector<DOFLoad*> transformToNodalLoads() override;

    string printInfo() override;

private:
    double startDistance;
    double endDistance;
    LoadComponent startComponents;
    LoadComponent endComponents;
    BeamElement3D *element;
};

#endif // BEAMDISTRIBUTEDLOAD_H