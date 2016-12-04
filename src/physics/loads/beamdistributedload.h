#ifndef BEAMDISTRIBUTEDLOAD_H
#define BEAMDISTRIBUTEDLOAD_H

#include "loadcomponent.h"

class BeamDistributedLoad : public ElementLoad
{
public:
    BeamDistributedLoad();
    BeamDistributedLoad(VectorXd valuesStart, double distStart, VectorXd valuesEnd, double distEnd);
private:
    double applyStartDistance;
    double applyEndDistance;
    LoadComponent startComponents;
    LoadComponent endComponents;
};

#endif // BEAMDISTRIBUTEDLOAD_H
