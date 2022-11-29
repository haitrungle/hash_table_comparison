#pragma once
/*
    All HashTable_* structs derived from the HashTable abstract class below.

    This header is included by the hashtable_*.cpp implementation files,
    which can cause circular include, hence the need for the include guard
    using the symbol MAIN. This way, the hashtable_*.cpp only get the
    HashTable abstract class declaration, while main.cpp gets all of the
    implementations.

    It's probably bad and ugly design, but as long as it works ...
*/

struct HashTable {
    virtual void Insert(unsigned x) = 0;
    virtual void Delete(unsigned x) = 0;
    virtual unsigned* Search(unsigned x) = 0;
};

#ifdef MAIN
#include "hashtable_sc.cpp"
#include "hashtable_lp.cpp"
#include "hashtable_qp.cpp"
#endif