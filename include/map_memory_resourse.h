#ifndef MAP_MEMORY_RESOURCE_H
#define MAP_MEMORY_RESOURCE_H

#include <map>
#include <memory_resource>
#include <stdexcept>

class MapMemoryResource : public std::pmr::memory_resource {
private:
    std::map<void*, std::size_t> allocations;
    std::pmr::memory_resource* upstream;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    explicit MapMemoryResource(std::pmr::memory_resource* upstream = std::pmr::get_default_resource());
    ~MapMemoryResource();

    MapMemoryResource(const MapMemoryResource&) = delete;
    MapMemoryResource& operator=(const MapMemoryResource&) = delete;
    MapMemoryResource(MapMemoryResource&&) = delete;
    MapMemoryResource& operator=(MapMemoryResource&&) = delete;
};

#endif // MAP_MEMORY_RESOURCE_H
