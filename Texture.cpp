#include "Texture.hpp"

Texture::Texture(NiSourceTextureRef node) {

    name = node->GetTextureFileName();

    if (node->IsTextureExternal()) {

        //cout << "Texture is an external file." << endl;
        cout << node->GetTextureFileName() << endl;

    } else {

        //cout << "Texture is included into the nif file." << endl;
        this->pixelData = DynamicCast<PixelData>(node->GetPixelData());
        this->pixelData->WriteTexture(name);
    }
}

string Texture::getName() {

    return name;
}

void Texture::PixelData::WriteTexture(string name) {

    unsigned char * buf = this->pixelData[0].data();

    //cout << name << endl;
    //cout << this->GetPixelFormat() << endl;

    if (this->GetPixelFormat() == PX_FMT_PAL8) {

        ofstream file("/home/plange/Projekte/3DPreview/Demo/models/" + name, ios::binary);

        // TODO: export tga
        file.write((char const *)buf, this->pixelData[0].size());

        file.close();

        return;
    }

    DDSFormat hdr;

    hdr.dwSize = 124;
    hdr.dwFlags = 0x000A1007;
    hdr.dwHeight = (unsigned int)this->GetHeight();
    hdr.dwWidth = (unsigned int)this->GetWidth();
    hdr.dwLinearSize = 0x00008000;
    hdr.dummy1 = 0;
    hdr.dwMipMapCount = this->numMipmaps;
    hdr.dummy2[0] = 0;
    hdr.dummy2[1] = 0;
    hdr.dummy2[2] = 0;
    hdr.dummy2[3] = 0;
    hdr.dummy2[4] = 0;
    hdr.dummy2[5] = 0;
    hdr.dummy2[6] = 0;
    hdr.dummy2[7] = 0;
    hdr.dummy2[8] = 0;
    hdr.dummy2[9] = 0;
    hdr.dummy2[10] = 0;
    hdr.ddsPixelFormat.dwSize = 0x00000020;
    hdr.ddsPixelFormat.dwFlags = DDPF_FOURCC;

    switch (this->GetPixelFormat()) {

        case PX_FMT_DXT5:
        case PX_FMT_DXT5_ALT:
            hdr.ddsPixelFormat.dwFourCC = FOURCC_DXT5;
            break;
        case PX_FMT_DXT1:
            hdr.ddsPixelFormat.dwFourCC = FOURCC_DXT1;
            break;
    }

    hdr.ddsPixelFormat.dwBPP = 24;
    hdr.ddsPixelFormat.dwRMask = 0x000000ff;
    hdr.ddsPixelFormat.dwGMask = 0x0000ff00;
    hdr.ddsPixelFormat.dwBMask = 0x00ff0000;
    hdr.ddsPixelFormat.dwAMask = 0x00000000;
    hdr.dwCaps = 0x00401008;
    hdr.dwCaps2 = 0;
    hdr.dwCaps3 = 0;
    hdr.dwCaps4 = 0;
    hdr.dwReserved2 = 0;

    ofstream file("/home/plange/Projekte/3DPreview/Demo/models/" + name, ios::binary);

    char magic[] = { 0x44, 0x44, 0x53, 0x20 };
    file.write(magic, 4);

    file.write((char const *)&hdr, sizeof(DDSFormat));
    file.write((char const *)buf, this->pixelData[0].size());

    file.close();
}