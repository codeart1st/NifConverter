#include "Texture.hpp"

Texture::Texture(NiObjectRef node) {

    if (!node->IsDerivedType(NiSourceTexture::TYPE)) {

        throw new exception();
    }

    NiSourceTextureRef data = DynamicCast<NiSourceTexture>(node);

    switch(data->GetMipMapFormat()) {
        case MIP_FMT_YES:
            cout << "Texture uses mip maps." << endl;
            break;
        case MIP_FMT_NO:
            cout << "Texture does not use mip maps." << endl;
            break;
        case MIP_FMT_DEFAULT:
            cout << "Use default setting." << endl;
            break;
        default:
            throw new exception();
    }

    switch(data->GetAlphaFormat()) {
        case ALPHA_NONE:
            cout << "No alpha blending; the texture is fully opaque." << endl;
            break;
        case ALPHA_BINARY:
            cout << "Texture is either fully transparent or fully opaque. There are no partially transparent areas." << endl;
            break;
        case ALPHA_SMOOTH:
            cout << "Full range of alpha values can be used from fully transparent to fully opaque including all partially transparent values in between." << endl;
            break;
        case ALPHA_DEFAULT:
            cout << "Use default setting." << endl;
            break;
        default:
            throw new exception();
    }

    switch(data->GetPixelLayout()) {
        case PIX_LAY_PALETTISED:
            cout << "Texture is in 8-bit paletized format." << endl;
            break;
        case PIX_LAY_HIGH_COLOR_16:
            cout << "Texture is in 16-bit high color format." << endl;
            break;
        case PIX_LAY_TRUE_COLOR_32:
            cout << "Texture is in 32-bit true color format." << endl;
            break;
        case PIX_LAY_COMPRESSED:
            cout << "Texture is compressed." << endl;
            break;
        case PIX_LAY_BUMPMAP:
            cout << "Texture is a grayscale bump map." << endl;
            break;
        case PIX_LAY_PALETTISED_4:
            cout << "Texture is in 4-bit paletized format." << endl;
            break;
        case PIX_LAY_DEFAULT:
            cout << "Use default setting." << endl;
            break;
        default:
            throw new exception();
    }

    if (data->IsTextureExternal()) {
        cout << "Texture is an external file." << endl;
        cout << data->GetTextureFileName() << endl;
    } else {
        cout << "Texture is included into the nif file." << endl;
        this->pixelData = DynamicCast<PixelData>(data->GetPixelData());
        this->pixelData->GetPixelBuffer();
    }
}

unsigned char* Texture::PixelData::GetPixelBuffer() {

}