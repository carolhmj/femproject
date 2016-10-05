#ifndef RESTRICTIONTYPES
#define RESTRICTIONTYPES
#include <vector>

//Tipos de restrições
enum class RestrictionTypes {
    FIXED,
    FREE
};

typedef std::vector<RestrictionTypes> RestrictionTypesVector;

#endif // RESTRICTIONTYPES

