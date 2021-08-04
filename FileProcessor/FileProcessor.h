#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <filesystem>
#include <map>
#include <utility>
#include <fstream>

namespace fs = std::filesystem;

class FileProcessor {
    public:
        FileProcessor(fs::path hot, fs::path bak, std::ofstream &ofs) : hotFolderPath(hot), bakFolderPath(bak), log(ofs) {};
        bool scan();
    private:
        fs::path hotFolderPath;
        fs::path bakFolderPath;
        std::ofstream &log;
        static constexpr const char* DELETE_KEYWORD = "delete_";
        std::map<std::string, time_t> hotFolderMap;
        void createBackup(const fs::path &srcPath, const fs::path &destPath);
        void deleteFiles(std::string fileName);
        void deleteFile(const fs::path &path);
        fs::path getFilepath(fs::path folderPath, const std::string &fileName, bool isBackup);
};

#endif // FILE_PROCESSOR_H
