#include "cache_mike.hh"
#include <iostream>
#pragma

int main()
{
    Cache::index_type indext = 2;
    Cache new_cache(1000);
    u_int32_t used = new_cache.space_used();
    std::cout << used << "\n";
    
    // Insert key, value
    u_int32_t const val = 400;
    Cache::val_type point = &val;
    u_int32_t size = sizeof(val);
    new_cache.set("key1",point,size);
    u_int32_t memused = new_cache.space_used();
    std::cout <<memused << " memused"<< '\n';

    // Get the value
    Cache::index_type sized;
    Cache::val_type thepoint= new_cache.get("key1",sized);
    const uint32_t& theval = *(static_cast<const u_int32_t*>(thepoint));
    std::cout << theval << "the value"<< '\n';

    // Delete a key
    new_cache.del("key1");
    memused = new_cache.space_used();
    std::cout <<memused << " memused"<< '\n';
}