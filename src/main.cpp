#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

namespace fs = std::filesystem;

// Function to write debugged processes to CSV
void log_debugged_process(const std::string& timestamp, const std::string& pid, const std::string& processName, const std::string& csvFile) {
    std::ofstream csvOut(csvFile, std::ios::app);
    if (!csvOut.is_open()) {
        std::cerr << "Failed to open CSV file for logging: " << csvFile << std::endl;
        return;
    }

    csvOut << timestamp << "," << pid << "," << processName << std::endl;
    csvOut.close();
}

// Function to check if a program has debug symbols
bool has_debug_symbols(const std::string& programPath) {
    std::string command = "file " + programPath + " | grep -i debug > /dev/null 2>&1";
    int result = system(command.c_str());
    return result == 0;
}

// Function to get running programs
std::vector<std::pair<std::string, std::string>> get_running_programs() {
    std::vector<std::pair<std::string, std::string>> programs; // Pair of PID and process path
    DIR* dir = opendir("/proc");
    struct dirent* entry;
    if (dir == nullptr) {
        std::cerr << "Failed to open /proc directory" << std::endl;
        return programs;
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            std::string pidDir(entry->d_name);
            if (pidDir.find_first_not_of("0123456789") == std::string::npos) {
                std::string cmdPath = "/proc/" + pidDir + "/exe";
                char buf[1024];
                ssize_t len = readlink(cmdPath.c_str(), buf, sizeof(buf) - 1);
                if (len != -1) {
                    buf[len] = '\0';
                    programs.emplace_back(pidDir, std::string(buf)); // Add PID and program path to the list
                }
            }
        }
    }
    closedir(dir);
    return programs;
}

int main() {
    std::string csvFile = "debugged_processes.csv";

    // Create or clear the CSV file and add headers
    std::ofstream csvOut(csvFile, std::ios::trunc);
    if (csvOut.is_open()) {
        csvOut << "Timestamp,PID,Process Name" << std::endl;
        csvOut.close();
    } else {
        std::cerr << "Failed to create or open CSV file: " << csvFile << std::endl;
        return 1;
    }

    bool toggle = true;
    while (toggle) {
        auto runningPrograms = get_running_programs();

        for (const auto& program : runningPrograms) {
            const std::string& pid = program.first;
            const std::string& programPath = program.second;

            if (has_debug_symbols(programPath)) {
                // Get current timestamp
                auto now = std::chrono::system_clock::now();
                std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
                std::string timestamp = std::ctime(&timeNow);
                timestamp.pop_back(); // Remove trailing newline

                std::cout << "Debug mode detected in: " << programPath << " (PID: " << pid << ")" << std::endl;

                // Log the debugged process
                log_debugged_process(timestamp, pid, programPath, csvFile);
            }
        }

        // Sleep for a while before checking again
        sleep(5); // Adjust the sleep time as needed
    }

    return 0;
}
