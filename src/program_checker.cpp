#include <iostream>         
#include <fstream>             
#include <string>             
#include <vector>             
#include <unordered_set>       
#include <unordered_map>       
#include <sstream>             
#include <algorithm>           

// This C++ program reads a CSV file and a list of filenames from the command line, 
// then checks each filename in the CSV file against the provided list. If a match is found, 
// it prints the matched filename to the console and tracks how many times each filename appears in the CSV file. 
// At the end, it outputs a summary showing the frequency of each matched filename. 


std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream stream(line);
    std::string token;
    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::unordered_set<std::string> read_filename_list(const std::string& filename) {
    std::unordered_set<std::string> filenameSet;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening filename list file: " << filename << std::endl;
        return filenameSet;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            filenameSet.insert(line);
        }
    }

    file.close();
    return filenameSet;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <csv_file> <filename_list>" << std::endl;
        return 1;
    }

    std::string csvFile = argv[1];
    std::string filenameListFile = argv[2];

    std::unordered_set<std::string> filenameSet = read_filename_list(filenameListFile);
    if (filenameSet.empty()) {
        std::cerr << "Filename list is empty or couldn't be loaded." << std::endl;
        return 1;
    }

    std::unordered_map<std::string, int> matchCounts;

    std::ifstream csv(csvFile);
    if (!csv.is_open()) {
        std::cerr << "Error opening CSV file: " << csvFile << std::endl;
        return 1;
    }

    std::string line;
    bool headerSkipped = false;

    while (std::getline(csv, line)) {
        if (!headerSkipped) {
            headerSkipped = true;
            continue;
        }
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() >= 3) {
            std::string filename = tokens[2];
            if (filenameSet.find(filename) != filenameSet.end()) {
                std::cout << "Match found: " << filename << std::endl;
                matchCounts[filename]++;
            }
        }
    }

    csv.close();
    std::cout << "\nSummary of Matches:\n";
    for (const auto& entry : matchCounts) {
        std::cout << "Filename: " << entry.first << " | Count: " << entry.second << std::endl;
    }

    return 0;
}
