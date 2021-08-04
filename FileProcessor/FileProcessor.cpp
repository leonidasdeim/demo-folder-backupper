#include <iostream>
#include <filesystem>
#include <map>
#include <cstring>

#include "FileProcessor.h"
#include "Utils.h"

bool FileProcessor::scan(void) {
    try {
        for (const auto & entry : fs::directory_iterator(hotFolderPath)) {
            if (!entry.is_directory()) {
                auto fileTime = Utils::formatTime(fs::last_write_time(entry));
                auto fileName = entry.path().filename().string();

                if (fileName.rfind(DELETE_KEYWORD, 0) == 0) {
                    deleteFiles(fileName);
                    return true;
                } else if (!hotFolderMap.contains(fileName)) {
                    log << "New file found in hot folder: " << fileName << std::endl;
                    hotFolderMap[fileName] = fileTime;
                    createBackup(entry.path(), getFilepath(bakFolderPath, fileName, true));
                } else if (hotFolderMap[fileName] != fileTime) {
                    log << "File has been modified: " << fileName << std::endl;
                    hotFolderMap[fileName] = fileTime;
                    createBackup(entry.path(), getFilepath(bakFolderPath, fileName, true));
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        log << e.what();
        return false;
    }

    return true;
}

void FileProcessor::createBackup(const fs::path &srcPath, const fs::path &destPath) {
    if (fs::exists(destPath)) {
        fs::remove(destPath);
    }
    fs::copy_file(srcPath, destPath);
    log << "Backup saved: " << destPath << std::endl;
}

void FileProcessor::deleteFiles(std::string fileName) {
    deleteFile(getFilepath(hotFolderPath, fileName, false));
    deleteFile(getFilepath(bakFolderPath, fileName.erase(0, std::strlen(DELETE_KEYWORD)), true));
    hotFolderMap.erase(fileName);
    log << "File and backup deleted: " << fileName << std::endl;
}

void FileProcessor::deleteFile(const fs::path &path) {
    if (fs::exists(path)) {
        fs::remove(path);
    }
}

fs::path FileProcessor::getFilepath(fs::path folderPath, const std::string &fileName, bool isBackup) {
    return folderPath /= (fileName + (isBackup ? "_bak" : ""));;
}