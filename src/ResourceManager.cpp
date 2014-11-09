#include "ResourceManager.hpp"

string ResourceManager::outputPath = "";
string ResourceManager::inputPath = "";

string ResourceManager::getOutputPath() {
    return outputPath;
}

string ResourceManager::getInputPath() {
    return inputPath;
}

void ResourceManager::setCurrentWorkspace(string outputPath, string inputPath, string filename) {

    string diffPath = filename.substr(inputPath.length());
    diffPath = diffPath.substr(0, diffPath.find_last_of("\\"));

    cout << "     Creating directory " << outputPath + diffPath << endl;

    system(("mkdir " + outputPath + diffPath).c_str());

    ResourceManager::inputPath = inputPath + diffPath;
    ResourceManager::outputPath = outputPath + diffPath;
}

ResourceManager::ResourceManager() {}

bool ResourceManager::checkIfDirectoryExists(const std::string& path) {

    DWORD ftyp = GetFileAttributesA(path.c_str());

    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!
}

void ResourceManager::listDirectory(string path, vector<string> &files) {

    DIR *dp;
    struct dirent *dirp;

    if((dp  = opendir(path.c_str())) == NULL) {

        if (errno == ENOTDIR) {

            // check if directory
            if (regex_match(path, regex(".*\\.nif", regex::icase))) {

                files.push_back(path);
            }

        } else {

            cout << "Error(" << errno << ") opening " << path << endl;
        }
        return;
    }

    while ((dirp = readdir(dp)) != NULL) {

        if (strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0) {

            listDirectory(path + "\\" + dirp->d_name, files);
        }
    }

    closedir(dp);
}