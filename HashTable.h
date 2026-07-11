//
// Created by gchri on 7/10/2026.
//

#ifndef PROJECT2_TRIFECTA_FINDER_HASHTABLE_H
#define PROJECT2_TRIFECTA_FINDER_HASHTABLE_H
#include <string>
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

// Node used for separate chaining when collisions occur.
struct HashNode {
    string prefix;
    vector<string> matches;
    HashNode* next;

    HashNode(string p, string song)
        : prefix(p), next(nullptr) {
        matches.push_back(song);
    }
};

class HashTable {
private:
    int tableSize;
    HashNode** table;

    // Converts text to lowercase so searches are not case-sensitive.
    string toLower(string text) const {
        for (char& c : text) {
            c = static_cast<char>(
                tolower(static_cast<unsigned char>(c))
            );
        }

        return text;
    }

    // Converts a string key into a bucket index.
    int hashFunction(string key) const {
        unsigned long hash = 5381;

        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }

        return static_cast<int>(hash % tableSize);
    }

public:
    // Constructor creates a fixed-size hash table.
    HashTable(int size) : tableSize(size) {
        table = new HashNode*[tableSize]();
    }

    // Destructor frees all linked-list nodes.
    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            HashNode* current = table[i];

            while (current) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] table;
    }

    // Inserts a prefix and its matching song display.
    void insert(string prefix, string song) {
        prefix = toLower(prefix);

        int index = hashFunction(prefix);
        HashNode* current = table[index];

        while (current) {
            if (current->prefix == prefix) {
                current->matches.push_back(song);
                return;
            }

            current = current->next;
        }

        HashNode* newNode = new HashNode(prefix, song);

        newNode->next = table[index];
        table[index] = newNode;
    }

    // Searches for all songs associated with a prefix.
    vector<string> search(string prefix) const {
        prefix = toLower(prefix);

        int index = hashFunction(prefix);
        HashNode* current = table[index];

        while (current) {
            if (current->prefix == prefix) {
                return current->matches;
            }

            current = current->next;
        }

        return {};
    }
};

#endif // PROJECT2_TRIFECTA_FINDER_HASHTABLE_H