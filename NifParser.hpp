#include "Mesh.hpp"

#include <niflib.h>
#include <obj/NiObject.h>

using namespace Niflib;

class NifParser {

public:

    NifParser(string);

    string toJSONString();

private:

    vector<NiObjectRef> list;
    vector<Mesh> meshes;
};