#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices)
{
    this->vertices = vertices;
    this->indices = indices;
}

