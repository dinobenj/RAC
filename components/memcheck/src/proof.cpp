#include <iostream>
#include <unordered_set>
#include <cstdlib>
#include <bits/stdc++.h>
/**
 * @brief Retrieves a global or static set o allocated mememory addresses.
 * 
 * @return std::unordered_set<void*>& Reference to the unordered set
 *         containing alocated memeory addresses.
 * 
 * @note Uses Dynamic Memory allocation for each call, which could result
 *       in memory leaks.
 * 
 */
std::unordered_set<void*>& get_allocated_addresses() {
    //static std::unordered_set<void*> allocated_addresses;  
    return *new std::unordered_set<void*>;
}

class mem_queue{
    public:
        /**
         * @brief Allocates memory for a mem_queue object and tracks and allocated address.
         * 
         * @param size Size in bytes of memory to allocate.
         * @return void* Pointer to the allocated memory.
         * 
         * @throws std::bad_alloc if memory allocation fails.
         * 
         * @note This function logs allocation size, address, and the pointer in a global set.
         */
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

        void add_to_queue(int i) {
            void* item = new mem_queue();
            allocated_addresses.insert(item);
            allocated_addresses.insert(&i);
            std::cout << "Item added to queue. Address: " << item << std::endl;
        }
        void memcheck_scan();
        void cleanup();
        std::unordered_set<void*> allocated_addresses;
};

/**
 * @brief Deallocates memory for a given pointer and removes it from the set of
 *        allocated addresses.
 * 
 * @param ptr Pointer to the memory to be deallocated.
 * 
 * @note This is a global operator delete function that handles pointers globally.
 *       If ptr is nullptr, no action is taken.
 */
void operator delete(void* ptr) noexcept {
    if (ptr) {
        get_allocated_addresses().erase(ptr);  
        std::free(ptr);  
    }
}

/**
 * @brief Checks and prints the current allocated memory addresses.
 * 
 * @note This function helps in debugging by displaying all currently allocated addresses.
 *       If no addresses are allocated, it reports that no memory is currently allocated.
 */
void memcheck_scan() {
    if (get_allocated_addresses().empty()) {
        std::cout << "No memory currently allocated." << std::endl;
    } else {
        std::cout << "Currently allocated memory addresses:" << std::endl;
        for (const auto& addr : get_allocated_addresses()) {
            std::cout << "Address: " << addr << std::endl;
        }
        std::cout << "Checksum of allocated addresses: " << std::hash<std::string>{}(std::to_string(reinterpret_cast<uintptr_t>(&get_allocated_addresses()))) << std::endl;
    }
}

/**
 * @brief Clears the set of allocated addresses, releasing all tracked allocations.
 * 
 * @note Useful for resetting allocation tracking, especially at program termination.
 */
void cleanup() {
    get_allocated_addresses().clear();
}

int main() {
    mem_queue* q = new mem_queue();
    memcheck_scan();
    int a = 4;
    q->add_to_queue(a);
    
    cleanup();


    return 0;
}
