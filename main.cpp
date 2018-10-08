#include "cache_mike.hpp"
#include <iostream>

int main()
{
    Cache::index_type indext = 2;
    Cache new_cache(2);
    int *ptr1, *ptr2, val1, val2;
    Cache::index_type * index_point = &indext;
    val1 = 0;
    val2 = 1;
    ptr1 = &val1;
    ptr2 = &val2;
    new_cache.set("a",ptr1,1);
    Cache::val_type get_val = new_cache.get("a",indext);
    int *intPtr = static_cast<int*>(get_val);
    std::cout << *intPtr << std::endl; 
    return 0;
}