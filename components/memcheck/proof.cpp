#include <iostream>
#include <unordered_set>
#include <cstdlib>

std::unordered_set<void*>& get_allocated_addresses() {
    //static std::unordered_set<void*> allocated_addresses;  
    return *new std::unordered_set<void*>;
}

class mem_queue{
    public:
        mem_queue(){};
        void* operator new(std::size_t size) {
            std::cout << "Allocating " << size << " bytes." << std::endl;
            void * ptr = std::malloc(size);  
            if (!ptr) {
                throw std::bad_alloc(); 
            }
            std::cout << "Allocated address: " << ptr << std::endl;
            get_allocated_addresses().insert(ptr); 
            std::cout << "Total allocated memory: " << get_allocated_addresses().size() << " blocks." << std::endl;
            return ptr;
        }
        void memcheck_scan();
        void cleanup();
    private:
        std::unordered_set<void*> allocated_addresses;
};


void operator delete(void* ptr) noexcept {
    if (ptr) {
        get_allocated_addresses().erase(ptr);  
        std::free(ptr);  
    }
}

void memcheck_scan() {
    if (get_allocated_addresses().empty()) {
        std::cout << "No memory currently allocated." << std::endl;
    } else {
        std::cout << "Currently allocated memory addresses:" << std::endl;
        for (const auto& addr : get_allocated_addresses()) {
            std::cout << "Address: " << addr << std::endl;
        }
    }
}
void cleanup() {
    get_allocated_addresses().clear();
}

int main() {
    mem_queue* q = new mem_queue();
    memcheck_scan();
    delete q;
    memcheck_scan();
    cleanup();


    return 0;
}
