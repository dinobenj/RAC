#include <cstdint>
#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../../src/../src/checksum_packet.h"
#include "reciever.h"

void reciever::start() {
    running = true;
    receive();
}

void reciever::stop() {
    running = false;
    close_socket();
}

void reciever::receive() {
    while (running) {
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(addr);
        buffer.resize(1024);
        int bytes = recvfrom(socket_fd, buffer.data(), buffer.size(), 0, (struct sockaddr*)&addr, &addr_len);
        if (bytes < 0) {
            std::cerr << "Error receiving data" << std::endl;
            exit(1);
        }
        std::string message(buffer.begin(), buffer.begin() + bytes);
        checksum_packet packet(message, 0);
        std::vector<uint8_t> checksum = packet.calculateChecksum();
        std::cout << "Received message: " << message << std::endl;
        std::cout << "Checksum: ";
        for (size_t i = 0; i < checksum.size(); i++) {
            std::cout << std::hex << (int)checksum[i] << " ";
        }
        std::cout << std::endl;
    }
}

void reciever::close_socket() {

}


void reciever::init_socket() {
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }
    std::cout << "Socket created and bound" << addr.sin_port << std::endl;
}




int main() {
    
    reciever r;
    r.start();
    r.stop();

    return 0;
}