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

    The default size of the table is 32. If the load factor exceeds 3/4, the
    table size is doubled, and rehashing occurs.
*/

template<class _Hasher>
struct HashTable_SC : HashTable {
    HashTable_SC() {
        count = 0;
        size = DEFAULT_TABLE_SIZE;
        buckets = new Entry[DEFAULT_TABLE_SIZE];
        hasher = _Hasher();
        hasher.set_size(size);
    }

    void Insert(unsigned x) {
        if (count > (size / 4) * 3) resize();

        unsigned i = hasher.hash(x);
        if (buckets[i].occupied()) {
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
        unsigned i = hasher.hash(x);
        Entry* p = &(buckets[i]);
        if (p->data == x) {
            if (p->next)
                buckets[i] = *(p->next);
            else
                buckets[i].data = -1;
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

    unsigned* Search(unsigned x) {
        unsigned i = hasher.hash(x);
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
        bool occupied() { return data + 1 != 0; };
    };
    const static int DEFAULT_TABLE_SIZE = 16;

    _Hasher hasher;
    Entry* buckets;
    int count;
    int size;

    void resize() {
        size = 2*size;
        hasher.set_size(size);
        Entry* new_buckets = new Entry[size];
        for (int i = 0; i < size/2; ++i) {
            Entry* p = &(buckets[i]);
            while (p && p->occupied()) {
                unsigned x = p->data;
                unsigned h = hasher.hash(x);
                Entry* q = &(new_buckets[h]);
                if (q->occupied()) {
                    while (q->next) {
                        q = q->next;
                    }
                    Entry* e = new Entry(x);
                    q->next = e;
                } else {
                    q->data = x;
                }
                p = p->next;
            }
        }
        Entry* old_buckets = buckets;
        buckets = new_buckets;
        delete[] old_buckets;
    }
};