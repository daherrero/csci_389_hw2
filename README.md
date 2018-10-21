### CS389 HW2: Hash it out.

####
DAVID HERRERO
MICHAEL KALANGE

#### IMPORTANT

Compile using:

`g++ -std=c++17 main.cpp`

#### Part 2: Testing

To test the two different evictors, `evictor_type_` must be changed in the `Impl` declaration. For FIFO evictor, use `"fifo"` and for LRU evictor, use `"lru"`. Also, uncomment the consequent evictor test in main.cpp and comment the other.

#### Part 3: Performance

We've implemented a universal hashing function for strings from the link(s): 
https://en.wikipedia.org/wiki/Universal_hashing and
http://www.cse.yorku.ca/~oz/hash.html

It takes some prime number that is large relative to the length of the string, bit shifts it by 5, and adds a character to that result, looping over all characters in the key, then returns the resulting hash.

#### Part 4: Collision resolution

Unordered map uses buckets which actually correspond to iterators into singly linked lists of the objects 'in' each bucket. There's no reason to fix what isn't broken so we've decided to just let unordered_map do its thing.

This link:
https://stackoverflow.com/questions/31112852/how-stdunordered-map-is-implemented/31113618#31113618
provides a stellar account of the mechanics involved in unordered_map's collision resolution.

#### Part 6: Eviction policy

Again, unordered map provides this functionality.
We just initialize my_cache_'s max load factor to be .5, and the table does automatic resizing to handle loads above that limit.
