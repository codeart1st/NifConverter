#include "Settings.hpp"

#include <regex>

Settings::Settings(int argc, char** argv) {

    if (argc < 2) throw UndefinedSettingsException();

    for (int i = 1; i < argc; i++) {

        if (regex_match(argv[i], regex("-[a-zA-Z]", regex_constants::extended))) {

            switch (argv[i][1]) {

                case 't':
                    this->externTextureName = argv[++i];
                    break;
                case 'o':
                    this->outputFileName = argv[++i];
                    break;
                default:
                    throw UndefinedSettingsException();
            }

        } else {

            this->inputFileName = argv[i];
        }
    }
}

string Settings::getExternTextureName() {
    return this->externTextureName;
}

string Settings::getOutputFileName() {
    return this->outputFileName;
}

string Settings::getInputFileName() {
    return this->inputFileName;
}

const char *UndefinedSettingsException::what() const noexcept (true) {

    return "Undefined settings properties detected.";
}
