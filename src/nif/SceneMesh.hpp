#ifndef _SCENE_MESH_HPP_
#define _SCENE_MESH_HPP_

#include "SceneNode.hpp"
#include "Material.hpp"

#include <niflib.h>
#include <obj/NiTriBasedGeom.h>
#include <obj/NiTriStripsData.h>
#include <obj/NiTriShapeData.h>

using namespace Niflib;

class SceneMesh : public SceneNode {

public:
    SceneMesh(NiTriBasedGeomRef);
};

#endif