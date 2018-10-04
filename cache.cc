#include "cache.hh"
#include <functional>
#include <memory>
#include <string>

Cache::Cache(index_type maxmem, 
            evictor_type evictor = [](){ return 0; },
            hash_func hasher = std::hash<std::string>())
{
    // INITIALIZER NEEDED HERE
}

void Cache::set(key_type key, val_type val, index_type size)
{
    // Code Needed
}

Cache::val_type Cache::get(key_type key, index_t& val_size) const
{
    // Code Needed
}

void Cache::del(key_type key)
{
    // Code Needed
}

Cache::index_type Cache::space_used() const
{
    // Code Needed
}