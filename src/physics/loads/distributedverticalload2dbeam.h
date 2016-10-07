#ifndef DISTRIBUTEDLOAD2DBEAM_H
#define DISTRIBUTEDLOAD2DBEAM_H
#include  "elementload.h"

class DistributedVerticalLoad2DBeam : public ElementLoad
{
public:
    DistributedVerticalLoad2DBeam();
private:
    double intensityInitialSide;
    double intensityFinalSide;
};

#endif // DISTRIBUTEDLOAD2DBEAM_H
