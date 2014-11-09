#include "SceneNode.hpp"

SceneNode::SceneNode(NiAVObjectRef node) {

    this->node["pos"][0] = node->GetLocalTransform().GetTranslation().x;
    this->node["pos"][1] = node->GetLocalTransform().GetTranslation().z;
    this->node["pos"][2] = -node->GetLocalTransform().GetTranslation().y;

    this->node["scl"] = node->GetLocalTransform().GetScale();

    this->node["rot"][0] = node->GetLocalTransform().GetRotation().AsQuaternion().x;
    this->node["rot"][1] = node->GetLocalTransform().GetRotation().AsQuaternion().z;
    this->node["rot"][2] = -node->GetLocalTransform().GetRotation().AsQuaternion().y;
    this->node["rot"][3] = node->GetLocalTransform().GetRotation().AsQuaternion().w;

    this->node["name"] = node->GetName();
    this->node["children"] = Json::arrayValue;
}

SceneNode * SceneNode::getLastChildren() {

    return (SceneNode*)&this->node["children"][ this->node["children"].size() - 1 ];
}

Value SceneNode::getNodeData() {

    return this->node;
}

void SceneNode::addChildren(SceneNode node) {

    this->node["children"].append(node.getNodeData());
}