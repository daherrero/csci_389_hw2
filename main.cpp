#include "cache_mike.hh"
#include <iostream>
#pragma

int main()
{
    Cache::index_type indext = 2;
    Cache new_cache(1000);
    u_int32_t used = new_cache.space_used();
    
    // Insert key, value
    u_int32_t const val = 4;
    Cache::val_type point = &val;
    u_int32_t size = sizeof(point);
    std::cout << size << " size from main \n";
    new_cache.set("key1",point,size);
    u_int32_t memused = new_cache.space_used();
    std::cout <<memused << " memused"<< '\n';

    // Get the value
    Cache::index_type sized;
    Cache::val_type thepoint= new_cache.get("key1",sized);
    const uint32_t& theval = *(static_cast<const u_int32_t*>(thepoint));
    std::cout << theval << "the value"<< '\n';

    // Delete a key
    new_cache.del("key0");
    new_cache.del("key1");
    u_int32_t memused1 = new_cache.space_used();
    std::cout <<memused1 << " memused after del"<< '\n';
}

void testSet()
{
    u_int32_t const val1 = 1;
    u_int32_t const val2 = 2;
    u_int32_t const val3 = 3;

    Cache::val_type point1, point2, point3;

    point1 = &val1;
    point2 = &val2;
    point3 = &val3;
    
    u_int32_t memused = new_cache.space_used();
    std::cout << "Current memory in use: " << memused << '\n';
    
}