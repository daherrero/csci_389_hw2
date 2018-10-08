#include "cache_mike.hh"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <string>

struct Cache::Impl 
{
        std::unordered_map<key_type,val_type> my_cache_;
        static index_type my_maxmem_;
        evictor_type my_evictor_;
        hash_func my_hasher_;
        index_type my_curmem_;
    };

Cache::Cache(index_type maxmem, 
            evictor_type evictor,
            hash_func hasher): pImpl_(new Impl())
{
    std::unordered_map<key_type,val_type> newCache;
    pImpl_ -> my_cache_ = newCache;
    pImpl_ -> my_evictor_ = evictor;
    pImpl_ -> my_maxmem_ = maxmem;
    pImpl_ -> my_hasher_ = hasher;
    pImpl_ -> my_curmem_ = 0;
}

Cache::~Cache() = default;

void Cache::set(key_type key, val_type val, index_type size)
{   
    if (((pImpl_->my_curmem_) + size) <= (pImpl_-> my_maxmem_))
    {
        (pImpl_->my_cache_).insert_or_assign(key,val);
        (pImpl_->my_curmem_)+=size;
    } else {
        while (((pImpl_->my_curmem_) + size) <= (pImpl_-> my_maxmem_))
        {
            auto it = (pImpl_->my_cache_).begin();
            (pImpl_->my_cache_).erase(it);
        }
        (pImpl_->my_cache_).insert_or_assign(key,val);
        (pImpl_->my_curmem_)+=size;
    }
}

Cache::val_type Cache::get(key_type key, index_type& val_size) const
{

    // GET KEY GET VALUE RETURN VALUE AND WRITE INTO ADDRESS PASSED AS PARAMETER
    auto search = (pImpl_->my_cache_).find(key);
    if (search != (pImpl_->my_cache_).end()) {
        val_type the_pointer =  &(search->second);
        return the_pointer;
    } else {
        return NULL;
    }
}

void Cache::del(key_type key)
{
    // need to ensure deletion of this object updates curmem
    (pImpl_->my_cache_).erase(key);
}

Cache::index_type Cache::space_used() const
{
    return pImpl_->my_curmem_;
}