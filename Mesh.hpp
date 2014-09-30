#include <niflib.h>

#include <obj/NiTriStripsData.h>
#include <obj/NiTriShapeData.h>

using namespace Niflib;

class Mesh {

public:
    Mesh(NiGeometryDataRef, vector<Matrix44>);

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