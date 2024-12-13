#include "../../../include/NOWAY/darray_memory_resourse.h"

darray_memory_resource::darray_memory_resource() = default;

darray_memory_resource::~darray_memory_resource() {
    for (auto &kv : allocated_) {
        ::operator delete(kv.first, std::nothrow);
    }
    allocated_.clear();
    free_blocks_.clear();
}

void* darray_memory_resource::do_allocate(std::size_t bytes, std::size_t alignment) {
    for (auto it = free_blocks_.lower_bound(bytes); it != free_blocks_.end(); ++it) {
        if (it->first >= bytes) {
            void* ptr = it->second;
            free_blocks_.erase(it);
            allocated_[ptr] = bytes;
            return ptr;
        }
    }

#if __cpp_aligned_new
    void* p = ::operator new(bytes, std::align_val_t(alignment));
#else
    (void)alignment;
    void* p = ::operator new(bytes);
#endif
    allocated_[p] = bytes;
    return p;
}

void darray_memory_resource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    (void)alignment;
    auto it = allocated_.find(p);
    if (it == allocated_.end()) {
        throw std::runtime_error("Invalid deallocation");
    }
    allocated_.erase(it);
    free_blocks_.insert(std::make_pair(bytes, p));
}

bool darray_memory_resource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
