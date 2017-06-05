#ifndef DYNAMICVECTORDOF_H
#define DYNAMICVECTORDOF_H

#include "vectordof.h"

/* VectorDOF, mas com os valores das derivadas. Os tipos e os restrictions são herdados de VectorDOF
 *
 */
class DynamicVectorDOF : public VectorDOF
{
public:
    DynamicVectorDOF(VectorXd values, vector<VectorDOFType> types, vector<RestrictionTypes> restrictions, vector<int> equationNumbers);
    DynamicVectorDOF(vector<VectorDOFType> types, vector<RestrictionTypes> restrictions, vector<int> equationNumbers);
private:
    VectorXd derivativeValues;
    VectorXd secondDerivativeValues;
};

#endif // DYNAMICVECTORDOF_H
