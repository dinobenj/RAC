#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

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

    return 0;
}
