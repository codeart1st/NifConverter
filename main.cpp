#include <iostream>
#include <niflib.h>
#include <obj/NiObject.h>
#include <obj/NiSourceTexture.h>
#include <obj/NiGeometryData.h>

#include "Settings.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

using namespace std;
using namespace Niflib;

// TODO: Find C++ JSON library again
// TODO: Find C++ dds texture library
// TODO: Use mixed JSON format with binary array data
// TODO: Check performance with live converting in node.js

int main(int argc, char** argv) {

    Settings settings(argc, argv);

    try {

        unsigned int version = GetNifVersion(settings.getSourceFile());

        cout << "VERSION : " << version << endl;

        vector<NiObjectRef> list = ReadNifList(settings.getSourceFile());

        for (int i = 0; i < list.size(); i++) {

            cout << list[i]->GetIDString() << endl;

            if (list[i]->IsDerivedType(NiGeometryData::TYPE)) {

                Mesh mesh(list[i]);

                cout << mesh.toString() << endl;
            }

            if (list[i]->IsDerivedType(NiSourceTexture::TYPE)) {

                Texture tex(list[i]);
            }
        }

    } catch (exception &e) {

        cerr << "ERROR: " << e.what() << endl;
    }

    return 0;
}