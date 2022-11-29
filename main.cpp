#define MAIN

#include "hasher/hasher.h"
#include "hashtable/hashtable.h"
#include <iostream>

int main(int argc, char* argv[]) {
    char* arg = argv[1];
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
            table = new HashTable_SC<Hasher_Div>();
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