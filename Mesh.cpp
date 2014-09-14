#include "Mesh.hpp"

Mesh::Mesh(NiObjectRef node) {

    if (!node->IsDerivedType(NiGeometryData::TYPE)) {

        throw new exception();
    }

    NiGeometryDataRef data = DynamicCast<NiGeometryData>(node);

    this->vertices = data->GetVertices();
    this->normals = data->GetNormals();
    this->colors = data->GetColors();
    this->indices = data->GetVertexIndices();

    for (int k = 0; k < data->GetUVSetCount(); k++) {

        uvs.push_back(data->GetUVSet(k));
    }
}

string Mesh::toString() {

    stringstream ss;

    for (int i = 0; i < this->vertices.size(); i++) {
        ss << this->vertices[i].x << " " << this->vertices[i].y << " "  << this->vertices[i].z << " ";
    }

    return ss.str();
}