#ifndef LAB0_DARRAY_MEMORY_RESOURSE_H
#define LAB0_DARRAY_MEMORY_RESOURSE_H

#pragma once
#include <memory_resource>
#include <map>
#include <cstddef>
#include <stdexcept>
#include <new>

class darray_memory_resource : public std::pmr::memory_resource {
public:
    darray_memory_resource();
    ~darray_memory_resource();

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    std::map<void*, std::size_t> allocated_;
    std::multimap<std::size_t, void*> free_blocks_;
};

#endif
