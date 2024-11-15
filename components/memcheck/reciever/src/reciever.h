#include <cstdint>
#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include <mutex>

class reciever {
    public:
        reciever();
        ~reciever();
        void start();
        void stop();
        void receive();

    private:
        int socket_fd;
        std::vector<uint8_t> buffer;
        std::mutex mtx;
        bool running;

        void init_socket();
        void close_socket();
};

