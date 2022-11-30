#pragma once
#include "hasher.h"
/*
    Hasher_Div: hashing by division

    Given the table size m and an integer x, the hash value is

        h(x) = x mod m

    This is about the simplest hashing method possible. The table size is
    most probably a power of 2, making it even simpler and weaker, due to
    all the high-order bits being ignored.

    We can make this somewhat more sophisticated by dividing by a prime
    number close to the table size instead, but dealing with prime number
    arithmetic is a bit of a pain.
*/

struct Hasher_Div : Hasher {
    unsigned hash(unsigned x) {
        return x % table_size;
    }
    void set_size(unsigned size) {
        table_size = size;
    }

private:
    unsigned table_size;
};