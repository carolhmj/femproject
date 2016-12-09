#ifndef LOADTYPE
#define LOADTYPE

enum class LoadType {
    NODE_LOAD,
    ELEMENT_LOAD
};

//Define se o componente é de força ou de momento
enum class LoadComponentType {
    FORCE,
    MOMENTUM
};

#endif // LOADTYPE

