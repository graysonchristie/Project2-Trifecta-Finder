//
// Created by gchri on 7/10/2026.
//

#ifndef PROJECT2_TRIFECTA_FINDER_HASHTABLE_H
#define PROJECT2_TRIFECTA_FINDER_HASHTABLE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;


// Node to create the buckets. Implements a linked list to store duing collissions
struct Node {
    string prefix;
    vector<string> matches;
    Node* next;

    // Node constructorggg
    Node(string p, string song) : prefix(p), next(nullptr) {
        matches.push_back(song);
    }
};

class HashTable {
private:
    int tableSize; // # of buckets
    Node** table;

    // Implementation of the hash function
    // transforms a string key into an array index
    int hashFunction(string key) {
        unsigned long hash = 5381;
        for (char c : key) hash = ((hash << 5) + hash) + c;
        return hash % tableSize;
    }

public:
    // Constructor (hash table with fixed size)
    HashTable(int size) : tableSize(size) {
        table = new Node*[tableSize]();
    }

    // Destructor
    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    // Insert a pair
    // Logic: Find bucket -> Create new node -> Point it to the current head -> Update head
    void insert(string prefix, string song) {
        int index = hashFunction(prefix);
        Node* current = table[index];

        while (current) {
            if (current->prefix == prefix) {
                current->matches.push_back(song);
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(prefix, song);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Searches based on key
    // Logic: Find bucket -> Traverse linked list -> Compare keys -> Return value
    vector<string> search(string prefix) {
        int index = hashFunction(prefix);
        Node* current = table[index];
        while (current) {
            if (current->prefix == prefix) return current->matches;
            current = current->next;
        }
        return {};
    }
};
#endif //PROJECT2_TRIFECTA_FINDER_HASHTABLE_H