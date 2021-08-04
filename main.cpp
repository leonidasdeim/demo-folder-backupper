#include <string>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <thread>
#include <chrono>
#include <fstream>
#include <signal.h>
#include <unistd.h>
#include <cstring>
#include <atomic>

#include "FileProcessor/FileProcessor.h"
 
namespace fs = std::filesystem;

std::atomic<bool> quit(false);      // SIGINT signal flag

void sigIntInit(void);
void gotSigInt(int);
bool checkAndCreateFolders(const fs::path &path, std::ofstream &log);     

int main(int argc, char* argv[]) {
    std::cout << "Aplication started" << std::endl;

    if (argc < 3 || argc > 3) {
        std::cout << "Please provide paths only for two folders" << std::endl;
        return 1;
    }

    sigIntInit();

    std::ofstream log("FolderBackupper.log");
    if (!log.is_open()) {
        std::cout << "Log file initialization failed" << std::endl;
        return 1;
    }

    log << "--- Program start ---" << std::endl;

    fs::path pathHot = argv[1];
    fs::path pathBak = argv[2];

    if (!checkAndCreateFolders(pathHot, log) || !checkAndCreateFolders(pathBak, log)) {
        return 1;
    }

    std::unique_ptr<FileProcessor> processor = std::make_unique<FileProcessor>(pathHot, pathBak, log);
    while(1) {
        if (!processor->scan() || quit.load()) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    log << "--- Program end ---" << std::endl;
}

bool checkAndCreateFolders(const fs::path &path, std::ofstream &log) {
    try {
        if (fs::exists(path)) {
            log << "Folder exists: " << path << std::endl;
        } else if (fs::create_directory(path)) {
            log << "Folder created: " << path << std::endl;
        } else {
            log << "Folder error: " << path << std::endl;
            return false;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        log << e.what();
        return false;
    }
    return true;
}

void sigIntInit(void) {
    struct sigaction sigAction;
    
    memset(&sigAction, 0, sizeof(sigAction));
    sigAction.sa_handler = gotSigInt;
    sigfillset(&sigAction.sa_mask);
    sigaction(SIGINT, &sigAction, NULL);
}

void gotSigInt(int) { 
    quit.store(true); 
}