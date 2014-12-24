#include "ConverterSettings.hpp"

#include <regex>
#include <iostream>

string ConverterSettings::inputPath;
string ConverterSettings::outputPath;
bool ConverterSettings::isAnimation;

ConverterSettings::ConverterSettings(int argc, char** argv) {

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

string ConverterSettings::getOutputPath() {
    return outputPath;
}

string ConverterSettings::getInputPath() {
    return inputPath;
}

bool ConverterSettings::isAnimationExport() {
    return isAnimation;
}

const char *UndefinedSettingsException::what() const noexcept (true) {

    return "Undefined settings properties detected. Call NifConverter.exe [INPUT\\PATH] [OUTPUT\\PATH].";
}
