/* Write a custom memory allocator
 *
 * motivation: C++ High Performance
 *
 * This allocator shows how an allocator can be implemented that creates
 * dynamic objects in stack memory, instead of in the free store.
 * As currently implemented this does not work yet for containers or
 * std::make_shared, or anything where the memory allocation is hidden inside
 * another object.
 */
#include <cstddef>
#include <iostream>
#include <memory>
using namespace std;

//--------------------------------------------------------------------------------MemoryPool

template <size_t N>
class MemoryPool {
public:
    MemoryPool() noexcept : used_(buffer_) {}

    MemoryPool(MemoryPool const &)            = delete;
    MemoryPool& operator=(MemoryPool const &) = delete;

    auto reset()       noexcept { used_ = buffer_; }
    auto used()  const noexcept { return static_cast<size_t>(used_ - buffer_); }
    static constexpr
    auto size()        noexcept { return N; }

    auto   allocate(size_t const n)                     -> std::byte*;
    auto deallocate(std::byte* const p, size_t const n) -> void;

private: // functions
    static
    auto align_up(size_t const n) noexcept -> size_t { return n+alignment-1 & ~(alignment-1); }
    auto pointer_is_in_buffer(std::byte const * const p) const noexcept -> bool {
        return std::uintptr_t(p) >= std::uintptr_t(buffer_) &&
               std::uintptr_t(p) <  std::uintptr_t(buffer_) + N; }

private: // data
    static constexpr size_t alignment = alignof(max_align_t);

    alignas(alignment) std::byte buffer_[N];
    std::byte* used_{};
};

template <size_t N>
auto MemoryPool<N>::allocate(size_t const n) -> std::byte* {
    auto const aligned_n = align_up(n);
    auto const available_bytes = static_cast<decltype(aligned_n)>(buffer_ + N - used_);
    if (available_bytes >= aligned_n) {
        auto* result = used_;
        used_ += aligned_n;
        return result;
    }
    return static_cast<std::byte*>(::operator new(n));
}

template <size_t N>
auto MemoryPool<N>::deallocate(std::byte* const p, size_t const n) -> void {
    if (pointer_is_in_buffer(p)) {
        auto const aligned_size = align_up(n);
        if (p + aligned_size == used_)
            used_ = p;
    }
    else ::operator delete(p);
}

//-----------------------------------------------------------------log free store allocation
// overload allocators to observe if any storage on the heap was used


auto allocated = size_t{0};

void* operator new(size_t size) {
    void* p = std::malloc(size);
    allocated += size;
    return p;
}

void operator delete(void* p) noexcept {
    return std::free(p);
}

//---------------------------------------------------------------------test custom allocator

auto user_memory_pool = MemoryPool<1024>{};

class User {
public:
    auto operator new(size_t const size) -> void* {
        return user_memory_pool.allocate(size);
    }
    auto operator delete(void* p) -> void {
        user_memory_pool.deallocate(static_cast<std::byte*>(p), sizeof(User));
    }
    auto operator new[](size_t const size) -> void* {
        return user_memory_pool.allocate(size);
    }
    auto operator delete[](void* p, size_t const size) -> void {
        // cerr << "about to call "
        user_memory_pool.deallocate(static_cast<std::byte*>(p), size);
    }
};

//------------------------------------------------------------------------------------------

int main() {
    auto user1 = new User{};
    cout << "heap  space used = " << allocated      << '\n';  // 0
    delete user1;

    auto users = new User[10];
    cout << "heap  space used = " << allocated      << '\n';  // 0
    delete [] users;

    auto user2 = std::make_unique<User>();
    cout << "heap  space used = " << allocated      << '\n';  // 0

    auto int_on_heap = new int;
    cout << "heap  space used = " << allocated      << '\n'; // 4 (calls default operator new)
    delete int_on_heap;

    return 0;
}
