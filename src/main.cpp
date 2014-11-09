#include <iostream>

#include "nif/NifParser.hpp"
#include "ResourceManager.hpp"
#include "Settings.hpp"

using namespace std;

int main(int argc, char** argv) {

    try {

        Settings settings(argc, argv);
        ResourceManager resourceManager;

        vector<string> files;

        resourceManager.listDirectory(settings.getInputPath(), files);

        // delete old data
        if (resourceManager.checkIfDirectoryExists(settings.getOutputPath())) {
            system(("rmdir /s /q " + settings.getOutputPath()).c_str());
        }

        for (int i = 0; i < files.size(); i++) {

            cout << setw(3) << round(((i+1) / (float)files.size()) * 100) << "% " << "Converting " << files[i] << endl;

            ResourceManager::setCurrentWorkspace(settings.getOutputPath(), settings.getInputPath(), files[i]);

            string output = ResourceManager::getOutputPath() + "\\item.json";
            ofstream file(output);

            try {

                NifParser parser(files[i]);

                file << parser.toJSONString() << endl;

                cout << "     Writing geometry to " << output << endl;

            } catch(exception &e) {

                cerr << e.what() << endl;
            }

            file.close();
        }

    } catch (exception &e) {

        cerr << e.what() << endl;
    }

    return 0;
}