#include "alloc.h"
#include "linked_list.h"


int main(int, char *[])
{

  auto dict = std::map<int, int, std::less<int>, std::allocator<std::pair<const int, int>>>{};

  for (auto i = 0; i < 10; ++i) 
  {
    dict.emplace(std::pair<int, int>(i, factorial(i)));
  }
  
  auto dict_custom = std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>, 10>>{};
 
  for (auto i = 0; i < 10; ++i)
  {
    dict_custom.emplace(std::pair<int, int>(i, factorial(i)));
    std::cout << std::endl;
  }

  printMap(dict_custom);
  
  LinkedList<int, std::allocator<int>> list_default;
  // 7. Insert 10 elements from 0 to 9
  for (int i = 0; i < 10; ++i) {
    list_default.push_back(i);
  }

 
  LinkedList<int, logging_allocator<int, 10>> list_custom;

  for (int i = 0; i < 10; ++i) {
    list_custom.push_back(i);
  }

 
  for (auto it = list_custom.cbegin(), itF(list_custom.cend()); it != itF; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

/*
  // TEST: Copy constructor (with same allocator types)
  auto list_cp = list_custom;
  for (auto it = list_cp.cbegin(), itF(list_cp.cend()); it != itF; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;


*/

  return 0;
}
