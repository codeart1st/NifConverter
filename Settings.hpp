#include <string>

using namespace std;

class Settings {

public:

    Settings(int, char**);

    string getOutputPath();
    string getInputPath();

private:

    string inputPath;
    string outputPath;
};

class UndefinedSettingsException : public exception {

public:
    virtual const char *what() const noexcept (true);
};