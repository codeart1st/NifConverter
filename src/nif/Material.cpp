#include "Material.hpp"

#include "Texture.hpp"

Material::Material(vector<NiPropertyRef> properties) {

    for (int k = 0; k < properties.size(); k++) {

        if (properties[k]->IsDerivedType(NiMaterialProperty::TYPE)) {

            NiMaterialPropertyRef materialProperty = DynamicCast<NiMaterialProperty>(properties[k]);

            Color3 ambient = materialProperty->GetAmbientColor();
            Color3 diffuse = materialProperty->GetDiffuseColor();

            material["DbgName"] = materialProperty->GetName();

            material["colorAmbient"][0] = ambient.r;
            material["colorAmbient"][1] = ambient.g;
            material["colorAmbient"][2] = ambient.b;

            material["colorDiffuse"][0] = diffuse.r;
            material["colorDiffuse"][1] = diffuse.g;
            material["colorDiffuse"][2] = diffuse.b;

        } else if (properties[k]->IsDerivedType(NiTexturingProperty::TYPE)) {

            NiTexturingPropertyRef texturingProperty = DynamicCast<NiTexturingProperty>(properties[k]);

            for (int j = 0; j < texturingProperty->GetTextureCount(); j++) {

                if (texturingProperty->HasTexture(j)) {

                    TexDesc desc = texturingProperty->GetTexture(j);

                    if (j == 0) {
                        // base texture
                        Texture tex(desc.source);
                        material["mapDiffuse"] = tex.getName();
                        //m.mapDiffuse, m.mapDiffuseRepeat, m.mapDiffuseOffset, m.mapDiffuseWrap, m.mapDiffuseAnisotropy );
                    }
                }
            }

        } else if (properties[k]->IsDerivedType(NiStencilProperty::TYPE)) {

            NiStencilPropertyRef stencilProperty = DynamicCast<NiStencilProperty>(properties[k]);

            if(stencilProperty->GetFaceDrawMode() == DRAW_BOTH) {
                material["doubleSided"] = true;
            }
        }
    }
}

Value Material::getMaterialProperties() {

    return material;
}