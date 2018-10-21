#include "testinglab.cpp"
#include <iostream>
#include <cassert>
#include <list>
#pragma
void testSet()
{
    // Make a cache large enough to hold 2 values;
    // (size of value is 8 bytes, size of void pointer)
    Cache test_cache(16);
    
    // Initialize some keys
    const std::string key1 = "one";
    const std::string key2 = "two";
    const std::string key3 = "three";
    const std::string key4 = "four";

    // Initialize list of keys
    std::list<std::string> list_of_keys({"key1", "key2", "key3", "key4"});

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
    printf("\nTEST FOR space_used AND insertion FUNCTIONS\n-------------------------------------------\n");

    u_int32_t memused = test_cache.space_used();
    printf("Current memory in use: %u \n", memused);
    printf("Inserting (key, value): (%s, %u)\n", key1.c_str(), val1);
    printf("Inserting (key, value): (%s, %u)\n", key2.c_str(), val2);

    u_int32_t size = sizeof(point1);
    test_cache.set("key1",point1,size);
    test_cache.set("key2",point2,size);

    memused = test_cache.space_used();
    printf("Current memory in use: %u \n", memused);
    assert(memused==(size*2));
    printf("Elements in the cache: ");
    for(std::list<std::string>::const_iterator i = list_of_keys.begin(); i != list_of_keys.end(); ++i)
    {
        std::string key_to_check = i->c_str();
        Cache::index_type sized;
        if (test_cache.get(key_to_check, sized) != NULL) {
            Cache::val_type thepoint= test_cache.get(key_to_check, sized);
            const uint32_t& theval = *(static_cast<const u_int32_t*>(thepoint));
            printf("[%s, %u] ", key_to_check.c_str(), theval);
        }
    }
    std::cout << std::endl;

    // Get a value just to ensure the storage and get works correctly
    printf("\nTEST FOR get FUNCTION\n---------------------\n");

    Cache::index_type sized;
    Cache::val_type thepoint= test_cache.get("key1",sized);
    const uint32_t& theval = *(static_cast<const u_int32_t*>(thepoint));
    printf("Getting value of key1. The value is: %u\n", theval);

    // Ensure resizing works (Trivial, already implemented in unordered map)
    // Implemented as asserts within the set function

    // Ensure hashing works (Trivial, unordered map takes hash function and uses it properly automatically)
    // If values end up in buckets, (and assuming the hash is a useful function) it's working...

    // Initialize size address
    Cache::index_type get_size = 0;

    // Changing key values
    printf("\nSWAP OF VALUES OF key1 and key2\n-------------------------------\n");

    //test_cache.set("key1",point2,size);
    //test_cache.set("key2",point1,size);
    printf("Swapped \n");

    // Delete a key
    printf("\nKEY DELETION\n------------\n");

    // Key 0 not in the cache
    test_cache.del("key0");
    // Key 1 is in the cache
    test_cache.del("key1");
    u_int32_t memused1 = test_cache.space_used();
    printf("%u memused after del \n", memused1);
    printf("Elements in cache: ");
    for(std::list<std::string>::const_iterator i = list_of_keys.begin(); i != list_of_keys.end(); ++i)
    {
        std::string key_to_check = i->c_str();
        Cache::index_type sized;
        if (test_cache.get(key_to_check, sized) != NULL) {
            Cache::val_type thepoint= test_cache.get(key_to_check, sized);
            const uint32_t& theval = *(static_cast<const u_int32_t*>(thepoint));
            printf("[%s, %u] ", key_to_check.c_str(), theval);
        }
    }
    std::cout << std::endl;

    // Accessing invalid key
    printf("\nACCESSING INVALID KEY\n---------------------\n");
    if (test_cache.get("key4", get_size) == NULL) {
        printf("Key \"%s\" is not in the cache \n", key4.c_str());
    }
    ///*
    // FIFO evictor test
    printf("\nFIFO EVICTOR TEST\n-----------------\n");
    test_cache.set("key3", point3, size);
    printf("Inserting (key, value): (%s, %u)\n", key3.c_str(), val3);
    if (test_cache.get(key1, get_size) == NULL) {
        printf("FIFO evictor is working. \n");
    }
    printf("Elements in the cache: ");
    for(std::list<std::string>::const_iterator i = list_of_keys.begin(); i != list_of_keys.end(); ++i)
    {
        std::string key_to_check = i->c_str();
        Cache::index_type sized;
        if (test_cache.get(key_to_check, sized) != NULL) {
            Cache::val_type thepoint= test_cache.get(key_to_check, sized);
            const uint32_t& theval = *(static_cast<const u_int32_t*>(thepoint));
            printf("[%s, %u] ", key_to_check.c_str(), theval);
        }
    }
    //*/
    /*
    // LRU evictor test (need to change evictor type in testinglab)
    // Access key 1 to make it last used.
    printf("\nLRU EVICTOR TEST\n----------------\n");

    test_cache.set("key1", point1, size);

    std::string key_to_check = "key2";
    if (test_cache.get(key_to_check, sized) != NULL) {
        Cache::val_type thepoint = test_cache.get(key_to_check, sized);
        const uint32_t &theval = *(static_cast<const u_int32_t *>(thepoint));
        printf("Accessing (key, value): (%s, %u)\n", key_to_check.c_str(), theval);
    }

    // Sets a new key, evicting the key with the most time unaccessed.
    test_cache.set("key3", point3, size);
    printf("Inserting (key, value): (%s, %u)\n", key3.c_str(), val3);

    printf("Elements in the cache: ");
    for(std::list<std::string>::const_iterator i = list_of_keys.begin(); i != list_of_keys.end(); ++i)
    {
        std::string key_to_check = i->c_str();
        Cache::index_type sized;
        if (test_cache.get(key_to_check, sized) != NULL) {
            Cache::val_type thepoint= test_cache.get(key_to_check, sized);
            const uint32_t& theval = *(static_cast<const u_int32_t*>(thepoint));
            printf("[%s, %u] ", key_to_check.c_str(), theval);
        }
    }

    key_to_check = "key1";
    if (test_cache.get(key_to_check, sized) == NULL) {
        printf("\nLRU evictor is working");
    }
    */
}

int main()
{
    testSet();
    std::cout << std::endl;
    return 0;
}

