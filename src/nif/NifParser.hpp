#ifndef _NIF_PARSER_HPP_
#define _NIF_PARSER_HPP_

#include "SceneNodeTransform.hpp"
#include "SceneNode.hpp"
#include "SceneMesh.hpp"

#include "../ConverterSettings.hpp"

#include <niflib.h>
#include <obj/NiNode.h>
#include <obj/NiLODNode.h>
#include <obj/NiExtraData.h>
#include <obj/NiRangeLODData.h>
#include <obj/NiTriBasedGeom.h>
#include <obj/NiBillboardNode.h>
#include <obj/NiStringExtraData.h>
#include <obj/NiTextKeyExtraData.h>

using namespace Niflib;

class NifParser {

public:
    NifParser(string);
    ~NifParser();

    string toJSONString();

private:

    void parseChildren(NiNodeRef, SceneNode *);
    void parseLODBranch(NiLODNodeRef, SceneNode *);

    bool rootFound;
    SceneNode * scene;
};

#endif