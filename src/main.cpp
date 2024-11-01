#include <iostream>
#include <filesystem>
#include <vector>

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

int main() {
    fs::path directory = "../components";
    std::vector<fs::path> files;

    findFiles(directory, files);

    for (const auto& file : files) {
        std::cout << file << std::endl;
    }
    compileCppFiles(files, "output");

    return 0;
}
