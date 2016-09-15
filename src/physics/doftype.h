#ifndef DOFTYPE
#define DOFTYPE

//Tipos possíveis de graus de liberdade
enum class DOFType {
    SCALAR,
    VECTOR
};

//Tipos possíveis de graus de liberdade vetoriais
enum class VectorDOFType {
    TRANSLATION,
    ROTATION
};

#endif // DOFTYPE

