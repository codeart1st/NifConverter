#include <iostream>
#include <fstream>

#include "NifParser.hpp"
#include "Settings.hpp"

using namespace std;

int main(int argc, char** argv) {

    try {

        Settings settings(argc, argv);

        NifParser parser(settings.getInputFileName());

        if (settings.getOutputFileName().length() > 0) {

            ofstream file(settings.getOutputFileName());

            file << parser.toJSONString();

            file.close();

        } else {

            cout << parser.toJSONString() << endl;
        }

    } catch (exception &e) {

        cerr << e.what() << endl;
    }

    return 0;
}