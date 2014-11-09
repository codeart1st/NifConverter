#ifndef _SCENE_NODE_TRANSFORM_HPP_
#define _SCENE_NODE_TRANSFORM_HPP_

#include "SceneNode.hpp"

#include <niflib.h>
#include <obj/NiNode.h>
#include <obj/NiKeyframeData.h>
#include <obj/NiTransformData.h>
#include <obj/NiTimeController.h>
#include <obj/NiTransformController.h>
#include <obj/NiTransformInterpolator.h>

#include <json/json.h>

using namespace Json;
using namespace Niflib;

class SceneNodeTransform : public SceneNode {

public:
    SceneNodeTransform(NiAVObjectRef);
};

#endif