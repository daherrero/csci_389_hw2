
#include "cache_mike.hh"
#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <string>
#pragma

struct Cache::Impl
{

    std::unordered_map<std::string,const void *> my_cache_;
    index_type maxmem_;
    evictor_type evictor_;
    hash_func hasher_;
    index_type memused_;

    Impl(index_type maxmem,
        evictor_type evictor,
        hash_func hasher) : maxmem_(maxmem), evictor_(evictor), hasher_(hasher), memused_(0)
    {
    }

    ~Impl() = default;

    // Add a <key, value> pair to the cache.
    // If key already exists, it will overwrite the old value.
    // Both the key and the value are to be deep-copied (not just pointer copied).
    // If maxmem capacity is exceeded, sufficient values will be removed
    // from the cache to accomodate the new value.
    void set(key_type key, val_type val, index_type size)
    {
        if ((memused_ + size) <= maxmem_)
        {
            my_cache_.insert_or_assign(key,val);
            memused_ += size;
            return;
        } else {
        while ((memused_ + size) >= maxmem_)
            evictor();
        }
        my_cache_.insert_or_assign(key,val);
        memused_ += size;
        return;
    }

    // Retrieve a pointer to the value associated with key in the cache,
    // or NULL if not found.
    // Sets the actual size of the returned value (in bytes) in val_size.
    val_type get(key_type key, index_type& val_size) const
    {
        auto search = (my_cache_).find(key);
        
        if (search != (my_cache_).end()) 
        {    
            // Update value stored in val_size if its in the cache.
            val_size = (uint32_t)sizeof(search->second);
            
            // Return pointer to the value.
            val_type point_to_val = search->second;
            return point_to_val;
        } else {
            return NULL;
        }
    }

    // Delete an object from the cache, if it's still there
    void del(key_type key)
    {
        index_type val_size = 0; 
        val_type is_in = get(key,val_size);

        if (is_in == NULL)
        {
            std::cout << "not in \n";
            return;
        }
        // Reduce the size of memused_appropriately 
        if (val_size != 0)
        {
            memused_ -= val_size;
        }
        my_cache_.erase(key);
    }

    // Returns the amount of memory used by all cache values (not keys).
    index_type space_used() const
    {
        return memused_;
    }

    void evictor()
    {

    }
};


  // Create a new cache object with a given maximum memory capacity.
Cache::Cache(index_type maxmem,
        evictor_type evictor,
        hash_func hasher) : pImpl_(new Impl(maxmem, evictor, hasher))
{
}

Cache::~Cache()
{    
}


// Add a <key, value> pair to the cache.
// If key already exists, it will overwrite the old value.
// Both the key and the value are to be deep-copied (not just pointer copied).
// If maxmem capacity is exceeded, sufficient values will be removed
// from the cache to accomodate the new value.
void Cache::set(key_type key, val_type val, index_type size)
{
    pImpl_->set(key,val,size);
}

// Retrieve a pointer to the value associated with key in the cache,
// or NULL if not found.
// Sets the actual size of the returned value (in bytes) in val_size.
Cache::val_type Cache::get(key_type key, index_type& val_size) const
{
    return pImpl_->get(key,val_size);
}

// Delete an object from the cache, if it's still there
void Cache::del(key_type key)
{
    pImpl_->del(key);
}

// Compute the total amount of memory used up by all cache values (not keys)
Cache::index_type Cache::space_used() const
{
    return pImpl_->space_used();
}