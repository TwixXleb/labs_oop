#include "../../include/map_memory_resourse.h"
#include <new>

MapMemoryResource::MapMemoryResource(std::pmr::memory_resource* upstream)
        : upstream(upstream) {}

MapMemoryResource::~MapMemoryResource() {
    if (!allocations.empty()) {
        throw std::runtime_error("Memory leak detected: not all memory was deallocated");
    }
}

void* MapMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    void* ptr = ::operator new(bytes, std::align_val_t(alignment));
    allocations[ptr] = bytes;
    return ptr;
}

void MapMemoryResource::do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) {
    auto it = allocations.find(ptr);
    if (it == allocations.end()) {
        throw std::runtime_error("Attempt to deallocate untracked memory");
    }
    allocations.erase(it);
    ::operator delete(ptr, bytes, std::align_val_t(alignment));
}

bool MapMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
