
#ifndef LAB0_MEMORY_RESOURSE_NEW_H
#define LAB0_MEMORY_RESOURSE_NEW_H

#include <memory_resource>
#include <map>

class ReusingMemoryResource : public std::pmr::memory_resource {
private:
    std::map<void*, std::size_t> freed_blocks;
    std::pmr::memory_resource* base_resource = std::pmr::get_default_resource();

public:
    ReusingMemoryResource() = default;
    ReusingMemoryResource(const ReusingMemoryResource&) = delete;
    ReusingMemoryResource& operator=(const ReusingMemoryResource&) = delete;
    ReusingMemoryResource(ReusingMemoryResource&&) = delete;
    ReusingMemoryResource& operator=(ReusingMemoryResource&&) = delete;

    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    ~ReusingMemoryResource() override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

#endif
