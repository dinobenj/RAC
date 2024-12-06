#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstdio>
#include <sys/types.h>
//#include <dirent.h>
#include <sys/stat.h>
//#include <unistd.h>

namespace fs = std::filesystem;


void compileCppFiles(const std::vector<fs::path>& cppFiles, const fs::path& outputDir) {
    for (const auto& file : cppFiles) {
        std::string outputName = outputDir / file.stem();
        std::string command = "g++" + file.string() + "-o " + outputName + " " + file.string();

        std::cout << "Compiling: " << file << std::endl;
        if (std::system(command.c_str()) != 0) {
            std::cerr << "Failed to compile: " << file << std::endl;
        } else {
            std::cout << "Compiled successfully: " << outputName << std::endl;
        }
    }
}

void findFiles(const fs::path& directory, std::vector<fs::path>& cppFiles) {
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
            cppFiles.push_back(entry.path());
        }
    }
}



bool has_debug_symbols(const std::string& programPath) {
    // Use 'file' command or 'nm' to check if the binary contains debugging symbols
    std::string command = "file " + programPath + " | grep -i debug";
    int result = system(command.c_str());
    return result == 0; // Returns 0 if "debug" is found in the output
}

std::vector<std::string> get_running_programs() {
    std::vector<std::string> programs;
    DIR* dir = opendir("/proc");
    struct dirent* entry;
    if (dir == nullptr) {
        std::cerr << "Failed to open /proc directory" << std::endl;
        return programs;
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            // Read PID from the directory entry
            std::string pidDir(entry->d_name);
            if (pidDir.find_first_not_of("0123456789") == std::string::npos) {
                std::string cmdPath = "/proc/" + pidDir + "/exe";
                char buf[1024];
                ssize_t len = readlink(cmdPath.c_str(), buf, sizeof(buf) - 1);
                if (len != -1) {
                    buf[len] = '\0';
                    programs.push_back(buf); // Add program path to the list
                }
            }
        }
    }
    closedir(dir);
    return programs;
}


int main() {
    bool toggle = false;
    while (toggle) {
        std::vector<std::string> runningPrograms = get_running_programs();
        
        for (const std::string& program : runningPrograms) {
            if (has_debug_symbols(program)) {
                std::cout << "Debug mode detected in: " << program << std::endl;
            }
        }

        // Sleep for a while before checking again
        sleep(5); // Adjust the sleep time as needed
    }
    fs::path directory = "../components";
    std::vector<fs::path> files;

    findFiles(directory, files);

    for (const auto& file : files) {
        std::cout << file << std::endl;
    }
    compileCppFiles(files, "output");

    return 0;
}
