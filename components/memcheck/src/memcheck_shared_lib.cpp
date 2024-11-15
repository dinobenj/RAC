#include "../include/memcheck_shared_lib.h"

void pipecommand(std::string strCmd) {
    std::array<char, 80> buf;
    FILE *pipe = _popen(strCmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "cannt open pipe for reading" << std::endl;
    }
    int c = 0;
    while (fgets(buf.data(), 80, pipe)) {
        c++;
        std::cout << c << "\t" << buf.data() << std::endl;
    }
    _pclose(pipe);
}

void SaySomething (std::string str) {
    std::cout << "I types:" << str << std::endl;
}