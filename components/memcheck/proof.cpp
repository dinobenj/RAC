#include <iostream>
#include <unordered_set>
#include <cstdlib>

bool in_new_operator = false;

std::unordered_set<void*>& get_allocated_addresses() {
    static std::unordered_set<void*> allocated_addresses;  
    return allocated_addresses;
}

void* operator new(std::size_t size) {
    if (in_new_operator) {
        return std::malloc(size);  
    }
    in_new_operator = true;
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

// void operator delete(void* ptr) noexcept {
//     if (ptr) {
//         get_allocated_addresses().erase(ptr);  
//         std::free(ptr);  
//     }
// }

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
    int* p1 = new int(10);
    double* p2 = new double(20);
    std::cout << "p1: " << *p1 << std::endl;
    std::cout << "p2: " << *p2 << std::endl;
    memcheck_scan();
    p2 = new double(25);
    delete p1;


    memcheck_scan();

    return 0;
}
