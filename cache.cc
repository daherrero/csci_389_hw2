#include "cache.hh"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <tuple>

class Cache::Impl 
{
    public:
        std::vector< std::tuple < key_type , val_type> > const myCache;
};

Cache::Cache(index_type maxmem, 
            evictor_type evictor = [](){ return 0; },
            hash_func hasher = std::hash<std::string>()) : pImpl_ = (new Impl())
{
    newCache = 
    pImpl_ -> myCache
}

Cache::~Cache() = default;

void Cache::set(key_type key, val_type val, index_type size)
{
    // Code Needed
}

Cache::val_type Cache::get(key_type key, index_type& val_size) const
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