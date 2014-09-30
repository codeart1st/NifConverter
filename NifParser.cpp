#include "NifParser.hpp"

#include <regex>

using namespace Json;

void NifParser::parseChildren(NiNodeRef root, vector<Matrix44> matrices) {

    vector<Matrix44> temp = matrices;
    temp.push_back(root->GetLocalTransform());

    //cout << "NODE ELEMENT: " << root->GetIDString() << endl;

    vector<NiAVObjectRef> children = root->GetChildren();

    for (int i = 0; i < children.size(); i++) {

        if (children[i]->IsDerivedType(NiNode::TYPE)) {

            NiNodeRef node = DynamicCast<NiNode>(children[i]);

            // Special switch node -> for switching between branches
            if (node->IsDerivedType(NiLODNode::TYPE)) {

                parseLODBranch(DynamicCast<NiLODNode>(node), temp);

            } else {

                parseChildren(node, temp);
            }

        } else {

            //cout << "OTHER STUFF: " << children[i]->GetIDString() << endl;

            if (children[i]->IsDerivedType(NiTriStrips::TYPE)) {

                //cout << "MESH DATA FOUND" << endl;
                NiTriStripsRef mesh = DynamicCast<NiTriStrips>(children[i]);

                vector<Matrix44> temp2 = temp;
                temp2.push_back(mesh->GetLocalTransform());

                this->meshes.push_back(Mesh(mesh->GetData(), temp2));

                this->materials.push_back(Material(mesh->GetProperties()));

            } else if (children[i]->IsDerivedType(NiTriShape::TYPE)) {

                //cout << "TRISHAPE MESH DATA FOUND" << endl;
                NiTriShapeRef mesh = DynamicCast<NiTriShape>(children[i]);

                vector<Matrix44> temp2 = temp;
                temp2.push_back(mesh->GetLocalTransform());

                this->meshes.push_back(Mesh(mesh->GetData(), temp2));

                this->materials.push_back(Material(mesh->GetProperties()));
            }
        }
    }
}

void NifParser::parseLODBranch(NiLODNodeRef root, vector<Matrix44> matrices) {

    vector<Matrix44> temp = matrices;
    temp.push_back(root->GetLocalTransform());

    vector<NiAVObjectRef> children = root->GetChildren();

    NiRangeLODDataRef rangeData = DynamicCast<NiRangeLODData>(root->GetLODLevelData());
    vector<LODRange> levels = rangeData->GetLODLevels();

    std::cout.precision(10);
    //cout << root->GetIDString() << " LOD branch with "  << levels.size() << " levels found" << endl;

    for (int i = 0; i < levels.size(); i++) {

        //cout << children[i]->GetIDString() << " LEVEL " << i << " from " << levels[i].nearExtent << " to " << levels[i].farExtent << endl;

        if (levels[i].nearExtent == 0) {

            //cout << "SELECT LOD LEVEL " << i << endl;

            if (children[i]->IsDerivedType(NiNode::TYPE)) {

                NiNodeRef node = DynamicCast<NiNode>(children[i]);

                parseChildren(node, temp);
            }
        }
    }
}

NifParser::NifParser(string filename) {

    NiObjectRef root = ReadNifTree(filename);

    if (root->IsDerivedType(NiNode::TYPE)) {

        NiNodeRef node = DynamicCast<NiNode>(root);

        vector<Matrix44> matrices;
        parseChildren(node, matrices);

    } else {

        cerr << "ERROR: Can't analyse scene graph" << endl;
    }
}

string NifParser::toJSONString() {

    Value root;
    Value metadata;
    Value materials;
    Value faces;
    Value vertices;
    Value normals;
    Value uvs;

    unsigned int offset = 0;
    unsigned int k = 0;

    for (int j = 0; j < this->meshes.size(); j++) {

        materials[j] = this->materials[j].getMaterialProperties();

        for (int i = 0; i < this->meshes[j].getVertices().size(); i++) {

            vertices[i + offset * 3] = this->meshes[j].getVertices()[i];
        }

        for (int i = 0; i < this->meshes[j].getNormals().size(); i++) {

            normals[i + offset * 3] = this->meshes[j].getNormals()[i];
        }

        for (int i = 0; i < this->meshes[j].getUVs().size(); i++) {

            uvs[i + offset * 2] = this->meshes[j].getUVs()[i];
        }

        vector<unsigned short> indices = this->meshes[j].getIndices();

        for (int i = 0; i < indices.size(); i++) {

            faces[k++] = 0b00101010;
            faces[k++] = indices[i + 0] + offset;
            faces[k++] = indices[i + 1] + offset;
            faces[k++] = indices[i + 2] + offset;
            faces[k++] = j;
            faces[k++] = indices[i + 0] + offset;
            faces[k++] = indices[i + 1] + offset;
            faces[k++] = indices[i + 2] + offset;
            faces[k++] = indices[i + 0] + offset;
            faces[k++] = indices[i + 1] + offset;
            faces[k++] = indices[i + 2] + offset;

            i += 2;
        }

        offset += this->meshes[j].getVertices().size() / 3;
    }

    metadata["version"] = 4;
    metadata["type"] = "Geometry";
    metadata["generator"] = "NetImmerse/Gamebryo™ Exporter";

    root["metadata"] = metadata;
    root["materials"] = materials;
    root["faces"] = faces;
    root["vertices"] = vertices;
    root["normals"] = normals;
    root["uvs"][0] = uvs;

    Json::FastWriter writer;

    return writer.write(root);
}
