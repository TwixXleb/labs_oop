#include "../../include/memory_resourse.h"

void* ReusingMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    for (auto it = freed_blocks.begin(); it != freed_blocks.end(); ++it) {
        if (it->second >= bytes) {
            void* ptr = it->first;
            freed_blocks.erase(it);
            return ptr;
        }
    }
    return base_resource->allocate(bytes, alignment);
}

void ReusingMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    freed_blocks[p] = bytes;
}

ReusingMemoryResource::~ReusingMemoryResource() {
    for (auto& block : freed_blocks) {
        base_resource->deallocate(block.first, block.second, alignment);
    }
}

bool ReusingMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}