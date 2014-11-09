#include <niflib.h>
#include <obj/NiSourceTexture.h>

using namespace Niflib;

#define DDSD_MIPMAPCOUNT           0x00020000
#define DDPF_FOURCC                0x00000004

// compressed texture pixel formats
#define FOURCC_DXT1  0x31545844
#define FOURCC_DXT2  0x32545844
#define FOURCC_DXT3  0x33545844
#define FOURCC_DXT4  0x34545844
#define FOURCC_DXT5  0x35545844

// DDS format structure
struct DDSFormat {
    unsigned int dwSize;
    unsigned int dwFlags;
    unsigned int dwHeight;
    unsigned int dwWidth;
    unsigned int dwLinearSize;
    unsigned int dummy1;
    unsigned int dwMipMapCount;
    unsigned int dummy2[11];
    struct {
        unsigned int dwSize;
        unsigned int dwFlags;
        unsigned int dwFourCC;
        unsigned int dwBPP;
        unsigned int dwRMask;
        unsigned int dwGMask;
        unsigned int dwBMask;
        unsigned int dwAMask;
    } ddsPixelFormat;
    unsigned int dwCaps;
    unsigned int dwCaps2;
    unsigned int dwCaps3;
    unsigned int dwCaps4;
    unsigned int dwReserved2;
};

class Texture {

public:
    Texture(NiSourceTextureRef);

    string getName();

private:

    class PixelData : public NiPixelData {

    public:
        void WriteTexture(string, string);
    };

    string name;
    Ref<PixelData> pixelData;
};