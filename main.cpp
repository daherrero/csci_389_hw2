#include "cache.hh"
#include <iostream>
#pragma
void testSet()
{
    // Make a cache large enough to hold 2 values;
    // (size of value is 8 bytes, size of void pointer)
    Cache test_cache(16);
    
    // Initialize some keys
    const std::string key1 = "key1";
    const std::string key2 = "key2";
    const std::string key3 = "key3";

    // Initialize some values
    u_int32_t const val1 = 1;
    u_int32_t const val2 = 2;
    u_int32_t const val3 = 3;

    Cache::val_type point1, point2, point3;

    // Initialize some pointers to the values
    point1 = &val1;
    point2 = &val2;
    point3 = &val3;
    

    // Test to make sure space_used and insertion functions work
    u_int32_t memused = test_cache.space_used();
    std::cout << "Current memory in use: " << memused << '\n';
    std::cout << "Inserting key,value: (" << key1 << val1 << ")"<<'\n'; 
    std::cout << "Inserting key,value: (" << key2 << val2 << ")"<<'\n';       
    
    u_int32_t size = sizeof(point1);
    test_cache.set("key1",point1,size);
    test_cache.set("key2",point2,size);

    memused = test_cache.space_used();
    std::cout << "Current memory in use: " << memused << '\n';
    assert(memused==(size*2));

    // Get a value just to ensure the storage and get works correctly
    Cache::index_type sized;
    Cache::val_type thepoint= test_cache.get("key1",sized);
    const uint32_t& theval = *(static_cast<const u_int32_t*>(thepoint));
    std::cout << theval << "the value"<< '\n';

    // Ensure resizing works (Trivial, already implemented in unordered map)
    // Implemented as asserts within the set function

    // Ensure hashing works (Trivial, unordered map takes hash function and uses it properly automatically)
    // If values end up in buckets, (and assuming the hash is a useful function) it's working...

    // Initialize size address
    Cache::index_type get_size = 0;

    // Changing key values
    std::cout << "Swap of values of key1 and key2.";
    test_cache.set("key1",point2,size);
    test_cache.set("key2",point1,size);
    for (auto i : test_cache)
        std::cout << "[" i.first << ", " << *(i.second) << "] ";

    // Delete a key 

    // Key 0 not in the cache
    test_cache.del("key0");
    // Key 1 is in the cache
    test_cache.del("key1");
    u_int32_t memused1 = test_cache.space_used();
    std::cout <<memused1 << " memused after del "<< '\n';

    // Accessing invalid key
    std::cout << "Accessing invalid key";
    if (test_cache.get("key4", get_size) == NULL) {
        std::cout << "Key \'key 4 \' is not in the cache\n";
    }

    // FIFO evictor test
    test_cache.set("key3", point3, size);
    std::cout << "Inserting key,value: (" << key3 << val3 << ")"<<'\n';
    for (auto i : test_cache)
        std::cout << "[" i.first << ", " << *(i.second) << "] ";
    if (test_cache.get(key1, get_size) == NULL) {
        std::cout << "FIFO evictor is working.\n";
    }

    // LRU evictor test (need to change evictor type in testinglab)
    // Access key 1 to make it last used.
    Cache::val_type pointer_to_get = test_cache.get(key1, &get_size);
    std::cout << "Accessing key,value: (" << key1 << *pointer_to_get << ")"<<'\n';

    // Sets a new key, evicting the key with the most time unaccessed.
    test_cache.set("key3", point3, size);
    std::cout << "Inserting key,value: (" << key3 << val3 << ")"<<'\n';
    std::cout << "Cache elements: " << '\n';
    for (auto i : test_cache)
        std::cout << "[" i.first << ", " << *(i.second) << "] ";
    if (test_cache.get(key2, get_size) == NULL) {
        std::cout << "LRU evictor is working.\n";
    }
}

int main()
{
    testSet();
    return 0;
}

