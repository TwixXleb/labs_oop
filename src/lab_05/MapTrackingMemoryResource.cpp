#include "../../include/MapTrackingMemoryResource.h"
#include <new>

MapTrackingMemoryResource::MapTrackingMemoryResource() = default;

MapTrackingMemoryResource::~MapTrackingMemoryResource() {
    for (auto &it : allocations_) {
        ::operator delete(it.first);
    }
    allocations_.clear();
}

void* MapTrackingMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    (void)alignment;
    void *ptr = ::operator new(bytes);
    allocations_.emplace(ptr, bytes);
    return ptr;
}

void MapTrackingMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    (void)bytes; (void)alignment;
    auto it = allocations_.find(p);
    if (it != allocations_.end()) {
        allocations_.erase(it);
        ::operator delete(p);
    } else {
        throw std::runtime_error("Attempt to deallocate unknown pointer.");
    }
}

bool MapTrackingMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
