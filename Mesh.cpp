#include "Mesh.hpp"

#include <iostream>

Mesh::Mesh(NiGeometryDataRef node, vector<Matrix44> matrices) {

    // TODO: das wieder in den hauptcode einpflegen, da bei abzweigungen immer doppelt berechnet wird
    Matrix44 temp = matrices[0];
    for (int i = 1; i < matrices.size(); i++) {

        temp = matrices[i] * temp;
    }

    vector<Vector3> vertices;
    vector<Vector3> normals;
    vector<Triangle> triangles;
    vector<TexCoord> uvs;

    if (node->IsDerivedType(NiTriStripsData::TYPE)) {

        NiTriStripsDataRef data = DynamicCast<NiTriStripsData>(node);

        vertices = data->GetVertices();
        normals = data->GetNormals();
        triangles = data->GetTriangles();

        if (data->GetUVSetCount() >= 1) {

            // TODO: handle more uv sets
            uvs = data->GetUVSet(0);
        }

    } else if (node->IsDerivedType(NiTriShapeData::TYPE)) {

        NiTriShapeDataRef data = DynamicCast<NiTriShapeData>(node);
        vertices = data->GetVertices();
        normals = data->GetNormals();
        triangles = data->GetTriangles();

        if (data->GetUVSetCount() >= 1) {

            // TODO: handle more uv sets
            uvs = data->GetUVSet(0);
        }

    } else {

        throw new exception();
    }

    for (int i = 0; i < vertices.size(); i++) {

        vertices[i] = temp * vertices[i];
        this->vertices.push_back(-vertices[i].y);
        this->vertices.push_back(vertices[i].z);
        this->vertices.push_back(vertices[i].x);
    }

    for (int i = 0; i < normals.size(); i++) {

        normals[i] = temp * normals[i];
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