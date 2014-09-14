#include <niflib.h>
#include <obj/NiGeometryData.h>

using namespace Niflib;

class Mesh {

public:
    Mesh(NiObjectRef);

    string toString();

private:
    vector<Vector3> vertices;
    vector<Vector3> normals;
    vector<Color4> colors;
    vector<int> indices;

    vector< vector<TexCoord> > uvs;
};