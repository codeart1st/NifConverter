#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include <string>

using namespace std;

class Settings {

public:

    Settings(int, char**);

    static string getOutputPath();
    static string getInputPath();
    static bool isAnimationExport();

private:

    static string inputPath;
    static string outputPath;
    static  bool isAnimation;
};

class UndefinedSettingsException : public exception {

public:
    virtual const char *what() const noexcept (true);
};

#endif