#include <niflib.h>
#include <obj/NiProperty.h>
#include <obj/NiStencilProperty.h>
#include <obj/NiTexturingProperty.h>
#include <obj/NiMaterialProperty.h>

#include <json/json.h>

using namespace Json;
using namespace Niflib;

class Material {

public:
    Material(vector<NiPropertyRef>);

    Value getMaterialProperties();

private:
    Value material;
};