#include <MatTexCollection.h>
#include "Material.hpp"

Material::Material(vector<NiPropertyRef> properties) {

    for (int k = 0; k < properties.size(); k++) {

        if (properties[k]->IsDerivedType(NiMaterialProperty::TYPE)) {

            NiMaterialPropertyRef materialProperty = DynamicCast<NiMaterialProperty>(properties[k]);

            Color3 ambient = materialProperty->GetAmbientColor();
            Color3 diffuse = materialProperty->GetDiffuseColor();
            Color3 emissive = materialProperty->GetEmissiveColor();
            Color3 specular = materialProperty->GetSpecularColor();

            material["specularCoef"] = materialProperty->GetGlossiness();
            //material["transparency"] = materialProperty->GetTransparency();
            material["DbgName"] = materialProperty->GetName();

            material["colorAmbient"][0] = ambient.r;
            material["colorAmbient"][1] = ambient.g;
            material["colorAmbient"][2] = ambient.b;

            material["colorDiffuse"][0] = diffuse.r;
            material["colorDiffuse"][1] = diffuse.g;
            material["colorDiffuse"][2] = diffuse.b;

            material["colorEmissive"][0] = emissive.r;
            material["colorEmissive"][1] = emissive.g;
            material["colorEmissive"][2] = emissive.b;

            material["colorSpecular"][0] = specular.r;
            material["colorSpecular"][1] = specular.g;
            material["colorSpecular"][2] = specular.b;

        } else if (properties[k]->IsDerivedType(NiTexturingProperty::TYPE)) {

            NiTexturingPropertyRef texturingProperty = DynamicCast<NiTexturingProperty>(properties[k]);

            for (int j = 0; j < texturingProperty->GetTextureCount(); j++) {

                if (texturingProperty->HasTexture(j)) {

                    TexDesc desc = texturingProperty->GetTexture(j);

                    if (j == 0) {
                        // base texture
                        Texture tex(desc.source);
                        material["mapDiffuse"] = tex.getName();
                        //material["mapDiffuse"] = "ConstellationDoubleSword.png";
                        //m.mapDiffuse, m.mapDiffuseRepeat, m.mapDiffuseOffset, m.mapDiffuseWrap, m.mapDiffuseAnisotropy );
                    }
                }
            }
        }
    }

    //material["shading"] = "phong"; // phong | basic
    material["doubleSided"] = true; // true | false
    //material["flipSided"] = true; // true | false

    /*material["blending"] = "";
    material["visible"] = "";
    material["vertexColors"] = "";


    material["mapLight"] = "";
    material["mapBump"] = "";
    material["mapNormal"] = "";
    material["mapSpecular"] = "";
    material["mapAlpha"] = "";
    material["mapBumpScale"] = "";*/
}

Value Material::getMaterialProperties() {

    return material;
}