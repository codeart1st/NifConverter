#include <iostream>
#include <cmath>
#include <dirent.h>
#include <regex>

#include "NifParser.hpp"
#include "Settings.hpp"

using namespace std;

// LINUX
int getdir (string dir, vector<string> &files) {

    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {

        if (regex_match(dirp->d_name, regex(".*\\.nif", regex::icase))) {

            files.push_back(dirp->d_name);
        }
    }
    closedir(dp);
    return 0;
}

/*
* PROBLEME mit tga als embedded texture
* PROBLEME bei setXXX mit den versteckten objekten den LOD stufen und den haaren -> wird von gamigo alles rausgenommen
* PROBLEME mit externen texturen
* REMOVE ANIMATION PARTS - PARTICLE - FROM WEAPONS
* AUSGABE in eigenen ordner ShortSword/SwhortSword.json + *.dds ...
 */
int main(int argc, char** argv) {

    try {

        Settings settings(argc, argv);

        vector<string> files;

        getdir(settings.getInputPath(), files);

        for (int i = 0; i < files.size(); i++) {

            cout << setw(3) << round(((i+1) / (float)files.size()) * 100) << "% " << "Converting " << files[i] << endl;

            NifParser parser(settings.getInputPath() + files[i]);

            ofstream file(settings.getOutputPath() + files[i] + ".json");

            file << parser.toJSONString();

            file.close();
        }

    } catch (exception &e) {

        cerr << e.what() << endl;
    }

    return 0;
}