#ifndef _SCENE_NODE_HPP_
#define _SCENE_NODE_HPP_

#include <niflib.h>
#include <obj/NiNode.h>

#include <json/json.h>

using namespace Json;
using namespace Niflib;

class SceneNode {

public:
    SceneNode(NiAVObjectRef);

    void addChildren(SceneNode);
    SceneNode * getLastChildren();
    Value getNodeData();

protected:
    Value node;
};

#endif