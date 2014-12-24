#include <windows.h>
#include <thread>
#include <vector>
#include <ctime>
#include <mutex>

#include "nif/NifParser.hpp"
#include "utils/ResourceManager.hpp"
#include "utils/ConverterSettings.hpp"

// TODO: Own log writer
// TODO: Improve settings class
// TODO: Improve animation export
// TODO: Add error overview on the end of the converting progress

std::mutex filesMutex;
int index = 0;
HANDLE hstdout = 0;

void foobar(const ConverterSettings settings, const vector<string> files) {

    int currentIndex;

    while (true) {

        filesMutex.lock();
        currentIndex = index++;
        filesMutex.unlock();

        if (currentIndex < files.size()) {

            // index is available
            std::stringstream ss;

            ss << "[" << setw(3) << round(((currentIndex+1) / (float)files.size()) * 100) << "%] " << "Converting " << files[currentIndex] << endl;

            SetConsoleTextAttribute(hstdout, 0x0A);
            cout << ss.str();
            SetConsoleTextAttribute(hstdout, 0x0F);

            ResourceManager::setCurrentWorkspace(settings.getOutputPath(), settings.getInputPath(), files[currentIndex]);

            string output = ResourceManager::getOutputPath() + "\\item.json";
            ofstream file(output);

            try {

                NifParser parser(files[currentIndex]);

                file << parser.toJSONString() << endl;

                //cout << "     Writing geometry to " << output << endl;

            } catch(exception &e) {

                cerr << e.what() << endl;
            }

            file.close();

        } else {

            // index out of range
            break;
        }
    }
}
int main(int argc, char** argv) {

    std::time_t start = std::time(NULL);

    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hstdout, &csbi);

    ConverterSettings settings(argc, argv);
    ResourceManager resourceManager;

    vector<string> files;

    resourceManager.listDirectory(settings.getInputPath(), files);

    // delete old data
    if (resourceManager.checkIfDirectoryExists(settings.getOutputPath())) {
        system(("rmdir /s /q " + settings.getOutputPath()).c_str());
    }

    //std::vector<std::thread> threads(std::thread::hardware_concurrency());
    std::vector<std::thread> threads(4);

    for (int i = 0; i < threads.size(); i++) {

        threads[i] = std::thread(foobar, settings, files);
    }

    for (auto &thread: threads) {

        thread.join();
    }

    std::cout << "finished in " << std::difftime(std::time(NULL), start) << " seconds" << std::endl;

    SetConsoleTextAttribute( hstdout, csbi.wAttributes );

    return 0;
}