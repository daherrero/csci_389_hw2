README.md

Problem 3:

We've implemented a universal hashing function for strings from the link(s): 
https://en.wikipedia.org/wiki/Universal_hashing and
http://www.cse.yorku.ca/~oz/hash.html

It takes some prime number that is large relative to the length of the string, bit shifts it by 5, and adds each character to that result, looping over all characters in the key, then returns the resulting hash.

Problem 4:

Unordered map uses buckets actually correspond to iterators into singly linked lists of the objects 'in' each bucket. There's no reason to fix what isn't broken so we've decided to just let unordered_map do its thing.

This link:
https://stackoverflow.com/questions/31112852/how-stdunordered-map-is-implemented/31113618#31113618
provides a stellar account of the mechanics involved in unordered_map's collision resolution.
