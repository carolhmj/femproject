#ifndef BEAMDISTRIBUTEDLOAD_H
#define BEAMDISTRIBUTEDLOAD_H

#include "loadcomponent.h"
#include "elementload.h"
#include "projectdefines.h"
#include <Eigen/Core>

using namespace Eigen;

class BeamDistributedLoad : public ElementLoad
{
public:
    BeamDistributedLoad();
    BeamDistributedLoad(VectorXd valuesStart, double distStart, VectorXd valuesEnd, double distEnd);
    VectorDOFLoad* getEquivalentNodal() override;
private:
    double applyStartDistance;
    double applyEndDistance;
    LoadComponent startComponents;
    LoadComponent endComponents;
};

#endif // BEAMDISTRIBUTEDLOAD_H
