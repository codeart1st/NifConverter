#include "Mesh.hpp"

#include <iostream>

Mesh::Mesh(NiObjectRef node) {

    if (!node->IsDerivedType(NiTriStripsData::TYPE)) {

        throw new exception();
    }

    NiTriStripsDataRef data = DynamicCast<NiTriStripsData>(node);

    vector<Vector3> vertices = data->GetVertices();
    vector<Vector3> normals = data->GetNormals();
    vector<Triangle> triangles = data->GetTriangles();
    vector<TexCoord> uvs = data->GetUVSet(0);

    for (int i = 0; i < vertices.size(); i++) {

        this->vertices.push_back(-vertices[i].y);
        this->vertices.push_back(vertices[i].z);
        this->vertices.push_back(vertices[i].x);
    }

    for (int i = 0; i < normals.size(); i++) {

        this->normals.push_back(-normals[i].y);
        this->normals.push_back(normals[i].z);
        this->normals.push_back(normals[i].x);
    }

    for (int i = 0; i < triangles.size(); i++) {

        this->indices.push_back(triangles[i].v1);
        this->indices.push_back(triangles[i].v3);
        this->indices.push_back(triangles[i].v2);
    }

    for (int i = 0; i < uvs.size(); i++) {

        this->uvs.push_back(uvs[i].u);
        this->uvs.push_back(uvs[i].v);
        //this->uvs.push_back(1 - uvs[i].v);
    }
}

vector<float> Mesh::getVertices() {

    return this->vertices;
}


vector<float> Mesh::getNormals() {

    return this->normals;
}

vector<unsigned short> Mesh::getIndices() {

    return this->indices;
}

vector<float> Mesh::getUVs() {

    return this->uvs;
}