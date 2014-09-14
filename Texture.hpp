#include <niflib.h>
#include <SOIL.h>
#include <obj/NiSourceTexture.h>

using namespace Niflib;

class Texture {

public:
    Texture(NiObjectRef);

private:
    int width;
    int height;

    class PixelData : public NiPixelData {

    public:
        unsigned char* GetPixelBuffer();
    };

    Ref<PixelData> pixelData;
};