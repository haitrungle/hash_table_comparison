#pragma once
#include "hashtable.h"
/*
    HashTable_SC: hash table using separate chaining with linked list

    The only supported data type is unsigned in the range of [0,UINT_MAX-1),
    due to UINT_MAX being used as the sentinel value for unoccupied buckets.

    Each bucket contains the data and a pointer to the next Entry in the 
    chain. On 32-bit platforms, this means only 1/2 of memory is used for 
    storing data, and on 64-bit platforms, this figure is even worse at
    1/3, or 1/4 if padding occurs.

    On collision, we traverse the chain to look for the data. If nothing is
    found, the new Entry is inserted at the end of the chain.

    The size of the table is fixed at 256.
*/

template<class _Hasher>
struct HashTable_SC : HashTable {
    HashTable_SC() {
        count = 0;
        size = DEFAULT_TABLE_SIZE;
        buckets = new Entry[DEFAULT_TABLE_SIZE];
        h = _Hasher();
        h.set_size(size);
    }

    void Insert(unsigned x) {
        int i = h.hash(x);
        if (buckets[i].data >= 0) {
            Entry* p = &(buckets[i]);
            if (p->data == x) return;
            while (p->next) {
                if (p->next->data == x) return;
                p = p->next;
            }
            Entry* e = new Entry(x);
            p->next = e;
        } else {
            buckets[i].data = x;
        }
        count++;
    }

    void Delete(unsigned x) {
        int i = h.hash(x);
        if (buckets[i].data >= 0) {
            Entry* p = &(buckets[i]);
            if (p->data == x) {
                buckets[i] = *(p->next);
                count--;
                return;
            }
            while (p->next) {
                if (p->next->data == x) {
                    p->next = p->next->next;
                    count--;
                    return;
                }
                p = p->next;
            }
        }
    }

    unsigned* Search(unsigned x) {
        int i = h.hash(x);
        Entry* p = &(buckets[i]);
        while (p) {
            if (p->data == x) {
                return &(p->data);
            }
            p = p->next;
        }
        return nullptr;
    }

   private:
    struct Entry {
        unsigned data;
        Entry* next;

        Entry() : data(-1), next(nullptr) {};
        Entry(unsigned d) : data(d), next(nullptr) {};
    };
    const static int DEFAULT_TABLE_SIZE = 256;

    _Hasher h;
    Entry* buckets;
    int count;
    int size;
};