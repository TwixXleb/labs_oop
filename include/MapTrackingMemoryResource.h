#pragma once
#include <map>
#include <cstddef>
#include <memory_resource>
#include <stdexcept>

class MapTrackingMemoryResource : public std::pmr::memory_resource {
public:
    MapTrackingMemoryResource();
    ~MapTrackingMemoryResource();

    MapTrackingMemoryResource(const MapTrackingMemoryResource&) = delete;
    MapTrackingMemoryResource& operator=(const MapTrackingMemoryResource&) = delete;
    MapTrackingMemoryResource(MapTrackingMemoryResource&&) = delete;
    MapTrackingMemoryResource& operator=(MapTrackingMemoryResource&&) = delete;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void  do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool  do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    std::map<void*, std::size_t> allocations_;
};
