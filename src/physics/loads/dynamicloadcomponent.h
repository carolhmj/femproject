#ifndef DYNAMICLOADCOMPONENT_H
#define DYNAMICLOADCOMPONENT_H

#include "loadcomponent.h"
#include <functional>

typedef std::function<VectorXd(int)> LoadFunction;

/*
 * Classe representa os componentes de uma força dinâmica. Logo, ele deve ter uma função que
 * recebe um tempo e retorna o valor da força desse tempo
 **/
class DynamicLoadComponent
{
public:
    DynamicLoadComponent(LoadFunction f);
    double getValueAtTime(unsigned int i, int t);
private:
    LoadFunction f;
    std::vector<LoadType> types;
};

#endif // DYNAMICLOADCOMPONENT_H
