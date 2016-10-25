#ifndef VECTORDOFLOAD_H
#define VECTORDOFLOAD_H
#include "dofload.h"
#include "vectordof.h"
#include "defines/projectdefines.h"
/*Classe que representa uma força em um grau de liberdade vetorial. Pode ser uma força ou um momento, dependendo do tipo do
* grau de liberdade correspondente.
*/
class VectorDOFLoad : public DOFLoad
{
public:
    VectorDOFLoad();
    VectorDOFLoad(VectorDOF *_vectordof, VectorXd _values);
    string printInfo() override;
    VectorDOF *getVdof() const;
    double getValue(unsigned i) const;

private:
    VectorDOF *vdof;
    VectorXd values;
};

#endif // VECTORDOFLOAD_H
