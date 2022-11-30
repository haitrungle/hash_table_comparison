#pragma once
#include "hashtable.h"
#include <iostream>
/*
    HashTable_LP: hash table using linear probing

    The only supported data type is unsigned in the range of [0,UINT_MAX-1),
    due to UINT_MAX being used as the sentinel value for unoccupied buckets.

    Each bucket contains the data and a boolean indicating if the bucket has 
    been deleted. The memory utilization rate is 4/5 in theory, though with 
    padding it is probably only 1/2.
    
    When an element is deleted, an empty slot is created in the probing 
    sequence, which might affect future searching, hence the need for the 
    deleted boolean flag.

    The default size of the table is 32. If the load factor exceeds 3/4, the
    table size is doubled, and rehashing occurs.
*/

template<class _Hasher>
struct HashTable_LP : HashTable {
    HashTable_LP() {
        count = 0;
        count_had_value = 0;
        size = DEFAULT_TABLE_SIZE;
        buckets = new Entry[size];
        hasher = _Hasher();
        hasher.set_size(size);
    }

    void Insert(unsigned x) {
        if (count_had_value > (size / 4) * 3) resize();

        unsigned h = hasher.hash(x);
        unsigned i = 0;
        while (buckets[p(h, i)].had_value) {
            if (buckets[p(h, i)].data == x) return;
            i++;
        }
        buckets[p(h, i)].data = x;
        buckets[p(h, i)].had_value = true;
        count++;
        count_had_value++;
    }

    void Delete(unsigned x) {
        unsigned h = hasher.hash(x);
        unsigned i = 0;
        while (buckets[p(h, i)].had_value) {
            if (buckets[p(h, i)].data == x) {
                buckets[p(h, i)].data = (unsigned)-1;
                count--;
                return;
            }
            i++;
        }
    }

    unsigned* Search(unsigned x) {
        unsigned h = hasher.hash(x);
        unsigned i = 0;
        while (buckets[p(h, i)].had_value && buckets[p(h, i)].data != x) {
            i++;
        }
        if (buckets[p(h, i)].data == x) return &(buckets[p(h, i)].data);
        return nullptr;
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            std::cout << "[" << i << "]: ";
            if (buckets[i].data + 1 != 0)
                std::cout << buckets[i].data << ",";
            std::cout << buckets[i].had_value << " ";
        }
        std::cout << "\n\n";
    }

   private:
    const static int DEFAULT_TABLE_SIZE = 32;
    struct Entry {
        unsigned data;
        bool had_value;

        Entry() : data(-1), had_value(false) {};
        Entry(unsigned d) : data(d), had_value(true) {};
        bool occupied() { return data + 1 != 0; }
    };
    _Hasher hasher;
    Entry* buckets;
    int count;
    int count_had_value; 
    int size;

    unsigned p(unsigned h, unsigned i) {
        return (h + i) % size;
    }

    void resize() {
        count_had_value = 0;
        size = 2*size;
        hasher.set_size(size);
        Entry* new_buckets = new Entry[size];
        for (int i = 0; i < size/2; ++i) {
            if (buckets[i].occupied()) {
                unsigned x = buckets[i].data;
                unsigned h = hasher.hash(x);
                unsigned j = 0;
                while (new_buckets[p(h, j)].had_value) {
                    if (new_buckets[p(h, j)].data == x) break;
                    j++;
                }
                new_buckets[p(h, j)].data = x;
                new_buckets[p(h, j)].had_value = true;
                count_had_value++;
            }
        }
        Entry* old_buckets = buckets;
        buckets = new_buckets;
        delete[] old_buckets;
    }
};