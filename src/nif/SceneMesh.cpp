#include "SceneMesh.hpp"

SceneMesh::SceneMesh(NiTriBasedGeomRef node) : SceneNode(DynamicCast<NiAVObject>(node)) {

    NiGeometryDataRef geometryData = node->GetData();

    vector<Vector3> vertices;
    vector<Vector3> normals;
    vector<Triangle> triangles;
    vector<vector<TexCoord>> uvs;

    if (geometryData->IsDerivedType(NiTriStripsData::TYPE)) {

        NiTriStripsDataRef data = DynamicCast<NiTriStripsData>(geometryData);

        vertices = data->GetVertices();
        normals = data->GetNormals();
        triangles = data->GetTriangles();

        for (int i = 0; i < data->GetUVSetCount(); i++) {

            uvs.push_back(data->GetUVSet(i));
        }

    } else if (geometryData->IsDerivedType(NiTriShapeData::TYPE)) {

        NiTriShapeDataRef data = DynamicCast<NiTriShapeData>(geometryData);
        vertices = data->GetVertices();
        normals = data->GetNormals();
        triangles = data->GetTriangles();

        for (int i = 0; i < data->GetUVSetCount(); i++) {

            uvs.push_back(data->GetUVSet(i));
        }

    } else {

        throw new exception();
    }

    this->node["material"] = Material(node->GetProperties()).getMaterialProperties();

    this->node["geometry"] = true;
    this->node["vertices"] = arrayValue;
    this->node["normals"] = arrayValue;
    this->node["faces"] = arrayValue;
    this->node["uvs"] = arrayValue;

    for (auto &v : vertices) {

        this->node["vertices"].append(v.x);
        this->node["vertices"].append(v.z);
        this->node["vertices"].append(-v.y);
    }

    for (auto &n : normals) {

        this->node["normals"].append(n.x);
        this->node["normals"].append(n.z);
        this->node["normals"].append(-n.y);
    }

    for (auto &set : uvs) {

        Value UVset = arrayValue;

        for (auto &coord : set) {

            UVset.append(coord.u);
            UVset.append(coord.v);
        }

        this->node["uvs"].append(UVset);
    }

    for (auto &t : triangles) {

        // TRIANGLE | FACE_VERTEX_NORMAL
        unsigned int flags = 0b00100000;

        if (this->node["uvs"].size() > 0) {
            // FACE_VERTEX_UV
            flags |= 0b00001000;
        }

        this->node["faces"].append(flags);

        this->node["faces"].append(t.v1);
        this->node["faces"].append(t.v2);
        this->node["faces"].append(t.v3);

        if (this->node["uvs"].size() > 0) {

            this->node["faces"].append(t.v1);
            this->node["faces"].append(t.v2);
            this->node["faces"].append(t.v3);
        }

        this->node["faces"].append(t.v1);
        this->node["faces"].append(t.v2);
        this->node["faces"].append(t.v3);
    }
}