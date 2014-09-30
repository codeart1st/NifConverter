#include "Mesh.hpp"
#include "Material.hpp"

#include <niflib.h>
#include <obj/NiObject.h>
#include <obj/NiLODNode.h>
#include <obj/NiTriStrips.h>
#include <obj/NiTriShape.h>
#include <obj/NiRangeLODData.h>
#include <obj/NiStringExtraData.h>

using namespace Niflib;

class NifParser {

public:

    NifParser(string);

    string toJSONString();

private:

    void parseChildren(NiNodeRef, vector<Matrix44>);
    void parseLODBranch(NiLODNodeRef, vector<Matrix44>);

    vector<NiObjectRef> list;
    vector<Mesh> meshes;
    vector<Material> materials;
};