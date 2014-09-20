#include <niflib.h>
#include <obj/NiTriStripsData.h>

using namespace Niflib;

class Mesh {

public:
    Mesh(NiObjectRef);

    vector<float> getVertices();
    vector<float> getNormals();
    vector<unsigned short> getIndices();
    vector<float> getUVs();

private:
    vector<float> vertices;
    vector<float> normals;
    vector<unsigned short> indices;
    vector<float> uvs;
};