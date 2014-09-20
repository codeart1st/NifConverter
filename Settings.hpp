#include <string>

using namespace std;

/**
* [-t texture.dds] [-o output.json] input.nif
*/
class Settings {

public:

    Settings(int, char**);

    string getExternTextureName();
    string getOutputFileName();
    string getInputFileName();

private:

    string externTextureName;
    string outputFileName;
    string inputFileName;
};

class UndefinedSettingsException : public exception {

public:
    virtual const char *what() const noexcept (true);
};