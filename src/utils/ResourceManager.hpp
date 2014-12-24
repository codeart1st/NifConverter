#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <iostream>
#include <vector>
#include <dirent.h>
#include <windows.h>
#include <regex>

using namespace std;

class ResourceManager {

public:

    ResourceManager();

    void listDirectory(string, vector<string>&);
    bool checkIfDirectoryExists(const std::string&);

    static void setCurrentWorkspace(string, string, string);

    static string getOutputPath();
    static string getInputPath();

private:

    static string outputPath, inputPath;
};

#endif