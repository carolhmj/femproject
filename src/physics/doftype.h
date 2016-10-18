#ifndef DOFTYPE
#define DOFTYPE
//Tipos possíveis de graus de liberdade
enum class DOFType {
    SCALAR,
    VECTOR
};

//Tipos possíveis de graus de liberdade vetoriais
//A rotação do nó representa a rotação do sistema de coordenadas do NÓ!!!!!!!
//(Não do elemento!!!!!!!!!!!!!)
//O desenho do elemento sai de um nó para os outros nós e chega tangente ao eixo x do nó
enum class VectorDOFType {
    TRANSLATION,
    ROTATION
};

#endif // DOFTYPE

