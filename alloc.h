#ifndef ALLOCATOR_LIB_H
#define ALLOCATOR_LIB_H

#include <iostream>
#include <memory>
#include <map>



template<typename T, std::size_t num_el>
struct logging_allocator {
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  template<typename U>
  struct rebind {
    using other = logging_allocator<U, num_el>;
  };

  logging_allocator() = default;

  ~logging_allocator() {}

  pointer allocate(std::size_t n) {
    std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    if (buff_ct + n > num_el) {
      throw std::bad_alloc();
    }
    if (!buff_ptr) {
      buff_ptr = reinterpret_cast<pointer>(malloc(num_el * sizeof(T)));
    }
    if (!buff_ptr) {
      throw std::bad_alloc();
    }
    pointer c_p = buff_ptr + buff_ct;
    buff_ct += n;
    return c_p;
  }

  void deallocate(pointer p, std::size_t n) {
    std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    if (!p) {
      return;
    }
    buff_ct -= n;
    if (buff_ct != 0) {
      return;
    }
    free(buff_ptr);
    buff_ptr = nullptr;
  }

  template<typename U, typename ...Args>
  void construct(U *p, Args &&...args) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    new(p) U(std::forward<Args>(args)...);
  };

  void destroy(pointer p) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    p->~T();
  }

private:
  pointer buff_ptr = nullptr;
  size_t  buff_ct  = 0;
};

int factorial(int value);

void printMap(std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>, 10>>& dict);

#endif //ALLOCATOR_LIB_H
