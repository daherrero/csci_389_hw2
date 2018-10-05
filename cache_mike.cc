#include "cache_mike.hh"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <tuple>

struct Cache::Impl 
{
    std::vector< std::tuple < key_type , val_type> > myCache;
};

Cache::Cache(index_type maxmem, 
            evictor_type evictor,
            hash_func hasher): pImpl_(new Impl())
{
    // HOPE HERE IS TO MAKE A VECTOR OF K-V tuples, and then assign pImpl_ to point to this vector
    // Current issue is the syntax of the vector
    newCache = void;
    pImpl_ -> &newCache;
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