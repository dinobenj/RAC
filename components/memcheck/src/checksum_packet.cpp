#include <cstdint>
#include <vector>
#include <iostream>

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
    return 0;
}