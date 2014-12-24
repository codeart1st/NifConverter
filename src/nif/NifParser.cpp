#include "NifParser.hpp"

string NifParser::toJSONString() {

    Value root;
    Value metadata;

    metadata["version"] = 1;
    metadata["type"] = "NetImmerse";
    metadata["generator"] = "NetImmerse/Gamebryo™ Exporter";

    root["metadata"] = metadata;
    root["root"] = this->scene->getNodeData();

    FastWriter writer;
    return writer.write(root);
}

NifParser::NifParser(string filePath) {

    this->scene = NULL;
    this->rootFound = false;

    NiObjectRef root = ReadNifTree(filePath);

    if (root->IsDerivedType(NiNode::TYPE)) {

        NiNodeRef node = DynamicCast<NiNode>(root);

        if (ConverterSettings::isAnimationExport()) {
            this->scene = new SceneNodeTransform(DynamicCast<NiAVObject>(node));
        } else {
            this->scene = new SceneNode(DynamicCast<NiAVObject>(node));
        }

        this->parseChildren(node, this->scene);

    } else {

        cerr << "ERROR: Can't analyse scene graph" << endl;
        throw exception();
    }
}

NifParser::~NifParser() {

    if (this->scene != NULL) {
        delete this->scene;
    }
}

void NifParser::parseLODBranch(NiLODNodeRef root, SceneNode * scene) {

    vector<NiAVObjectRef> children = root->GetChildren();

    NiRangeLODDataRef rangeData = DynamicCast<NiRangeLODData>(root->GetLODLevelData());
    vector<LODRange> levels = rangeData->GetLODLevels();

    //cout << "     NiLODNode detected with "  << levels.size() << " branches" << endl;

    for (int i = 0; i < levels.size(); i++) {

        if (levels[i].nearExtent == 0) {

            //cout << "     Select LODLevel " << i << " : " << children[i]->GetName();
            //cout << " (" << levels[i].nearExtent << " to " << levels[i].farExtent << ")" << endl;

            if (children[i]->IsDerivedType(NiNode::TYPE)) {

                NiNodeRef node = DynamicCast<NiNode>(children[i]);

                if (ConverterSettings::isAnimationExport()) {
                    scene->addChildren(SceneNodeTransform(DynamicCast<NiAVObject>(node)));
                } else {
                    scene->addChildren(SceneNode(DynamicCast<NiAVObject>(node)));
                }

                parseChildren(node, scene->getLastChildren());

                return;
            }
        }
    }
}

void NifParser::parseChildren(NiNodeRef root, SceneNode * scene) {

    // skip zMode10 -> HarlekinCover
    list<NiExtraDataRef> extraData = root->GetExtraData();
    for (auto &data : extraData) {

        if (data->IsDerivedType(NiStringExtraData::TYPE)) {

            NiStringExtraDataRef str = DynamicCast<NiStringExtraData>(data);

            if (str->GetData().find("zMode10") != string::npos) {
                return;
            }

        } else if (data->IsDerivedType(NiTextKeyExtraData::TYPE)) {

            // skip animation stuff
            return;
        }
    }

    // skip >>NOOUTLINE<<
    if (root->GetName().compare("NOOUTLINE") == 0) {
        return;
    }

    // skip >>Scene Root<< in sub nodes
    if (this->rootFound && root->GetName().compare("Scene Root") == 0) {
        return;
    } else {
        this->rootFound = true;
    }

    vector<NiAVObjectRef> children = root->GetChildren();

    for (auto &child : children) {

        // not supported billboard plane at the moment - orthogonal to camera
        if (child->IsDerivedType(NiNode::TYPE) && !child->IsSameType(NiBillboardNode::TYPE)) {

            NiNodeRef node = DynamicCast<NiNode>(child);

            if (ConverterSettings::isAnimationExport()) {
                scene->addChildren(SceneNodeTransform(DynamicCast<NiAVObject>(node)));
            } else {
                scene->addChildren(SceneNode(DynamicCast<NiAVObject>(node)));
            }

            // Special switch node -> for switching between branches
            if (node->IsDerivedType(NiLODNode::TYPE)) {

                parseLODBranch(DynamicCast<NiLODNode>(node), scene->getLastChildren());

            } else {

                parseChildren(node, scene->getLastChildren());
            }

        } else if (child->IsDerivedType(NiTriBasedGeom::TYPE)) {

            NiTriBasedGeomRef node = DynamicCast<NiTriBasedGeom>(child);

            scene->addChildren((SceneNode)SceneMesh(node));
        }
    }
}