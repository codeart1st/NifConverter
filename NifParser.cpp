#include "NifParser.hpp"

#include "Texture.hpp"

#include <json/json.h>

using namespace Json;

NifParser::NifParser(string filename) {

    try {

        this->list = ReadNifList(filename);
        bool temp = false;

        for (int i = 0; i < list.size(); i++) {

            if (list[i]->IsDerivedType(NiGeometryData::TYPE)) {

                if (temp) {
                    this->meshes.push_back(this->list[i]);
                    break;
                } else {
                    temp = true;
                }
            }

            if (list[i]->IsDerivedType(NiSourceTexture::TYPE)) {

                Texture tex(list[i]);
            }
        }

    } catch (exception &e) {

        cerr << "ERROR: " << e.what() << endl;
    }
}

string NifParser::toJSONString() {

    Value root;
    Value metadata;
    Value faces;
    Value vertices;
    Value normals;
    Value uvs;

    for (int i = 0; i < this->meshes[0].getVertices().size(); i++) {

        vertices[i] = this->meshes[0].getVertices()[i];
    }

    for (int i = 0; i < this->meshes[0].getNormals().size(); i++) {

        normals[i] = this->meshes[0].getNormals()[i];
    }

    for (int i = 0; i < this->meshes[0].getUVs().size(); i++) {

        uvs[i] = this->meshes[0].getUVs()[i];
    }

    vector<unsigned short> indices = this->meshes[0].getIndices();

    int k = 0;
    for (int i = 0; i < indices.size(); i++) {

        faces[k++] = 0b00101000;
        faces[k++] = indices[i + 0];
        faces[k++] = indices[i + 1];
        faces[k++] = indices[i + 2];
        faces[k++] = indices[i + 0];
        faces[k++] = indices[i + 1];
        faces[k++] = indices[i + 2];
        faces[k++] = indices[i + 0];
        faces[k++] = indices[i + 1];
        faces[k++] = indices[i + 2];

        i += 2;
    }

    metadata["version"] = 4;
    metadata["type"] = "Geometry";
    metadata["generator"] = "NetImmerse/Gamebryo™ Exporter";

    root["metadata"] = metadata;
    root["faces"] = faces;
    root["vertices"] = vertices;
    root["normals"] = normals;
    root["uvs"][0] = uvs;

    Json::StyledWriter writer;

    return writer.write(root);
}
