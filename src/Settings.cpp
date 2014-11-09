#include "Settings.hpp"

#include <regex>
#include <iostream>

string Settings::inputPath;
string Settings::outputPath;
bool Settings::isAnimation;

Settings::Settings(int argc, char** argv) {

    if (argc < 2) throw UndefinedSettingsException();

    isAnimation = false;

    for (int i = 1; i < argc; i++) {

        if (regex_match(argv[i], regex("--export-animation", regex_constants::extended))) {

            isAnimation = true;

        } else {

            if (this->inputPath.length() == 0) {

                this->inputPath = argv[i];

            } else if (this->outputPath.length() == 0) {

                this->outputPath = argv[i];
            }
        }
    }
}

string Settings::getOutputPath() {
    return outputPath;
}

string Settings::getInputPath() {
    return inputPath;
}

bool Settings::isAnimationExport() {
    return isAnimation;
}

const char *UndefinedSettingsException::what() const noexcept (true) {

    return "Undefined settings properties detected. Call NifConverter.exe [INPUT\\PATH] [OUTPUT\\PATH].";
}
