#include <cstdint>
#include <vector>
#include <iostream>
#include "checksum_packet.h"

checksum_packet::checksum_packet(std::string str, unsigned int seq) {
    message = str;
    seqNum = seq;
    checksum_arr = calculateChecksum();
}

void checksum_packet::setMessage(std::string str) {
    message = str;
}

void checksum_packet::setSeqNum(unsigned int num) {
    seqNum = num;
}

std::string checksum_packet::getMessage() {
    return message;
}

int checksum_packet::getLength() {
    return message.length();
}

std::vector<uint8_t> checksum_packet::calculateChecksum() {
    std::vector<uint8_t> data;
    for (size_t i = 0; i < message.length(); i++) {
        data.push_back(message[i]);
    }
    data.push_back(seqNum & 0xFF);
    data.push_back((seqNum >> 8) & 0xFF);
    return data;
    
}



uint16_t calculateChecksum(const std::vector<uint8_t>& data) {
    uint32_t sum = 0;

    for (size_t i = 0; i < data.size(); i += 2) {
        uint16_t word = data[i];
        if (i + 1 < data.size()) {
            word = (word << 8) | data[i + 1];
        }
        sum += word;

        if (sum > 0xFFFF) {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }
    }

    return ~sum & 0xFFFF;
}



int main() {
    std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04, 0x05};
    uint16_t checksum = calculateChecksum(data);
    std::cout << "Checksum: " << std::hex << checksum << std::endl;

    checksum_packet packet("Hello, world!", 0x1234);
    std::cout << "Message: " << packet.getMessage() << std::endl;
    std::cout << "Length: " << packet.getLength() << std::endl;
    for (int i = 0; i < packet.calculateChecksum().size(); i++) {
        std::cout << "Checksum byte " << i << ": " << std::hex << (int)packet.calculateChecksum()[i] << std::endl;
    }


    return 0;
}