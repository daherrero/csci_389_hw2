#include "cache_mike.hh"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <string>

class Cache::Impl 
{
    public:
        std::unordered_map<key_type,val_type> * my_cache_;
        static index_type my_maxmem_;
        evictor_type my_evictor_;
        hash_func my_hasher_;
        index_type my_curmem_;
    };

Cache::Cache(index_type maxmem, 
            evictor_type evictor,
            hash_func hasher): pImpl_(new Impl())
{
    // HOPE HERE IS TO MAKE A VECTOR OF K-V tuples, and then assign pImpl_ to point to this vector
    std::unordered_map<key_type,val_type> * newCache = new std::unordered_map<key_type,val_type>;
    pImpl_ -> my_cache_ = newCache;
    pImpl_ -> my_evictor_ = evictor;
    pImpl_ -> my_maxmem_ = maxmem;
    pImpl_ -> my_hasher_ = hasher;
    pImpl_ -> my_curmem_ = 0;
}

Cache::~Cache() = default;

void Cache::set(key_type key, val_type val, index_type size)
{   
    // For clarity, we change the
    
    
    if ((pImpl_->my_curmem_ + size) <= pImpl_-> my_maxmem_)
    {
        *(pImpl_->my_cache_).insert_or_assign(key,val);
    }
}

Cache::val_type Cache::get(key_type key, index_type& val_size) const
{
    std::unordered_map<key_type,val_type> * the_cache = (pImpl_->my_cache_);
    auto search = (*the_cache).find(key);
    if (search != (*the_cache).end()) {
        val_type val_address = &(search->second);
        return val_address;
    } else {
        return NULL;
    }
}

void Cache::del(key_type key)
{
    // Code Needed
}

Cache::index_type Cache::space_used() const
{
    // Code Needed
}