#include <iostream>
#include <cstdlib>

class checksum_packet
{
    private:
        std::string message;
        unsigned int checksum;  // this is a 16 bit checksum
        unsigned int seqNum;

    public:
        checksum_packet(std::string str, unsigned int seq);
        void setMessage(std::string str);
        void setSeqNum(unsigned int num);
        std::string getMessage();
        int getLength();
        unsigned int calculateChecksum();
        int getChecksum();
        bool getSeqNum();
};