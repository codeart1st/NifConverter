#include "Settings.hpp"

#include <regex>

Settings::Settings(int argc, char** argv) {

    if (argc < 2) throw UndefinedSettingsException();

    for (int i = 1; i < argc; i++) {

        if (regex_match(argv[i], regex("-[a-zA-Z]", regex_constants::extended))) {

            /*switch (argv[i][1]) {

                case 't':
                    this->externTextureName = argv[++i];
                    break;
                case 'o':
                    this->outputFileName = argv[++i];
                    break;
                default:
                    throw UndefinedSettingsException();
            }*/

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
    return this->outputPath;
}

string Settings::getInputPath() {
    return this->inputPath;
}

const char *UndefinedSettingsException::what() const noexcept (true) {

    return "Undefined settings properties detected.";
}
