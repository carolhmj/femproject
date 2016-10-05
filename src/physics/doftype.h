#ifndef DOFTYPE
#define DOFTYPE
#include <vector>
//Tipos possíveis de graus de liberdade
enum class DOFType {
    SCALAR,
    VECTOR
};

typedef std::vector<DOFType> DOFTypeVector;

//Tipos possíveis de graus de liberdade vetoriais
enum class VectorDOFType {
    TRANSLATION,
    ROTATION
};

typedef std::vector<VectorDOFType> VectorDOFTypeVector;

#endif // DOFTYPE

