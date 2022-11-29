#define MAIN

#include "hasher/hasher.h"
#include "hashtable/hashtable.h"
#include <iostream>
#include <unordered_set>

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    char* arg = argv[1];
    if (arg[0] == '0') {
        std::unordered_set<unsigned> set;
        char buffer[8];
        unsigned x;
        while (std::cin >> buffer >> x) {
            if (buffer[0] == 's') {  // search
                if (set.find(x) != set.end())
                    std::cout << x << " was found\n";
                else
                    std::cout << x << " does not exist\n";
            } else if (buffer[0] == 'i') {  // insert
                set.insert(x);
            } else {  // delete
                if (set.find(x) != set.end()) {
                    std::cout << x << " was deleted successfully\n";
                    set.erase(x);
                } else {
                    std::cout << x << " does not exist\n";
                }
            }
        }
        return 0;
    }
    HashTable* table;
    switch (arg[0]) {
        case '1':
            table = new HashTable_SC<Hasher_Div>();
            break;
        case '2':
            table = new HashTable_SC<Hasher_Mul>();
            break;
        case '3':
            table = new HashTable_LP<Hasher_Div>();
            break;
        case '4':
            table = new HashTable_LP<Hasher_Mul>();
            break;
        case '5':
            table = new HashTable_QP<Hasher_Div>();
            break;
        case '6':
            table = new HashTable_QP<Hasher_Mul>();
            break;
        default:
            std::cerr << "No argument given";
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
    return 0;
}