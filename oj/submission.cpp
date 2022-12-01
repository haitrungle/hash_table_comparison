#include <iostream>
#include <unordered_set>

struct HashTable {
    virtual void Insert(unsigned x) = 0;
    virtual void Delete(unsigned x) = 0;
    virtual unsigned* Search(unsigned x) = 0;
};

struct Hasher {
    virtual unsigned hash(unsigned x) = 0;
    virtual void set_size(unsigned size) = 0;

private:
    unsigned table_size;
};


struct Hasher_Mul : Hasher {
    unsigned hash(unsigned x) {
        return (x * A) >> (32 - p);
    }
    void set_size(unsigned size) {
        table_size = size;
        unsigned power = 0;
        while (size >> power) ++power;
        p = power - 1;
    }

private:
    unsigned table_size;
    unsigned p; // = floor(log2(table_size))
    const static unsigned A = 2654435769; // = 2^32 * (sqrt(5)-1)/2
};

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

template<class _Hasher>
struct HashTable_QP : HashTable {
    HashTable_QP() {
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
        return (h + i*(i+1)/2) % size;
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
    const static int DEFAULT_TABLE_SIZE = 32;

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

int main(int argc, char* argv[]) {
    HashTable* table;
    int implementation = 1;
    switch (implementation) {
        case 1:
            table = new HashTable_SC<Hasher_Div>();
            break;
        case 2:
            table = new HashTable_SC<Hasher_Mul>();
            break;
        case 3:
            table = new HashTable_LP<Hasher_Div>();
            break;
        case 4:
            table = new HashTable_LP<Hasher_Mul>();
            break;
        case 5:
            table = new HashTable_QP<Hasher_Div>();
            break;
        case 6:
            table = new HashTable_QP<Hasher_Mul>();
            break;
        default:
            std::cerr << "Invalid implementation";
            return 1;
    }

    char buffer[8];
    unsigned x;
    while (std::cin >> buffer >> x) {
        if (buffer[0] == 's') {  // search
            if (table->Search(x))
                std::cout << x << " was found\n";
            else
                std::cout << x << " does not exist\n";
        } else if (buffer[0] == 'i') {  // insert
            table->Insert(x);
        } else {  // delete
            if (table->Search(x)) {
                std::cout << x << " was deleted successfully\n";
                table->Delete(x);
            } else {
                std::cout << x << " does not exist\n";
            }
        }
    }
}