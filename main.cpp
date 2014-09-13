#include <iostream>
#include <niflib.h>
#include <obj/NiObject.h>

#include "Settings.hpp"

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

        cout << list[0]->asString() << endl;

    } catch (exception &e) {

        cerr << "ERROR: " << e.what() << endl;
    }

    return 0;
}