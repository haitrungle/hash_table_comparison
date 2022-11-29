#pragma once
/*
    All Hasher_* structs derived from the Hasher abstract class below.

    This header is included by the hasher_*.cpp implementation files, which
    cause circular include, hence the need for the include guard using the
    symbol MAIN. This way, the hashtable_*.cpp only get the HashTable abstract
    class declaration, while main.cpp gets all of the implementations.

    It's probably bad and ugly design, but as long as it works ...
*/

struct Hasher {
    virtual unsigned hash(unsigned x) = 0;
    virtual void set_size(unsigned size) = 0;

private:
    unsigned table_size;
};

#ifdef MAIN
#include "hasher_div.cpp"
#include "hasher_mul.cpp"
#endif