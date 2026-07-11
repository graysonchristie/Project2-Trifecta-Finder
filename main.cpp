#include <chrono>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "SongLoader.h"
#include "HashTable.h"
#include "Trie.h"

using namespace std;

// Displays up to the first 10 search results.
void displayResults(const vector<string>& results) {
    if (results.empty()) {
        cout << "\nNo matches found." << endl;
        return;
    }

    cout << "\nFound " << results.size() << " matches:" << endl;

    for (size_t i = 0; i < results.size() && i < 10; i++) {
        cout << i + 1 << ". " << results[i] << endl;
    }

    if (results.size() > 10) {
        cout << "...and " << results.size() - 10
             << " more matches." << endl;
    }
}

// Runs one hash-table autocomplete search.
void runHashTableSearch(HashTable& hashTable) {
    string query;

    cout << "\nEnter an artist or song prefix: ";
    getline(cin, query);

    if (query.empty()) {
        cout << "Search cannot be empty." << endl;
        return;
    }

    auto start = chrono::high_resolution_clock::now();

    vector<string> results = hashTable.search(query);

    auto end = chrono::high_resolution_clock::now();

    auto searchTime =
        chrono::duration_cast<chrono::nanoseconds>(end - start);

    displayResults(results);

    cout << "\nHash table search time: "
         << searchTime.count()
         << " nanoseconds" << endl;
}

// Runs one Trie autocomplete search.
void runTrieSearch(Trie& trie) {
    string query;

    cout << "\nEnter an artist or song prefix: ";
    getline(cin, query);

    if (query.empty()) {
        cout << "Search cannot be empty." << endl;
        return;
    }

    auto start = chrono::high_resolution_clock::now();

    vector<string> results = trie.search(query);

    auto end = chrono::high_resolution_clock::now();

    auto searchTime =
        chrono::duration_cast<chrono::nanoseconds>(end - start);

    displayResults(results);

    cout << "\nTrie search time: "
         << searchTime.count()
         << " nanoseconds" << endl;
}

// Compares both structures using the exact same query.
void compareSearches(HashTable& hashTable, Trie& trie) {
    string query;

    cout << "\nEnter an artist or song prefix: ";
    getline(cin, query);

    if (query.empty()) {
        cout << "Search cannot be empty." << endl;
        return;
    }

    const int trials = 100;

    vector<string> hashResults;
    vector<string> trieResults;

    auto hashStart = chrono::high_resolution_clock::now();

    for (int i = 0; i < trials; i++) {
        hashResults = hashTable.search(query);
    }

    auto hashEnd = chrono::high_resolution_clock::now();

    auto trieStart = chrono::high_resolution_clock::now();

    for (int i = 0; i < trials; i++) {
        trieResults = trie.search(query);
    }

    auto trieEnd = chrono::high_resolution_clock::now();

    auto hashTotal =
        chrono::duration_cast<chrono::nanoseconds>(
            hashEnd - hashStart
        ).count();

    auto trieTotal =
        chrono::duration_cast<chrono::nanoseconds>(
            trieEnd - trieStart
        ).count();

    double hashAverage =
        static_cast<double>(hashTotal) / trials;

    double trieAverage =
        static_cast<double>(trieTotal) / trials;

    cout << "\nSearch comparison for \"" << query << "\":" << endl;

    cout << "Hash Table average: "
         << hashAverage
         << " nanoseconds" << endl;

    cout << "Trie average: "
         << trieAverage
         << " nanoseconds" << endl;

    cout << "\nHash Table matches: "
         << hashResults.size() << endl;

    cout << "Trie matches: "
         << trieResults.size() << endl;

    if (hashAverage < trieAverage) {
        cout << "\nHash Table was faster for this search." << endl;
    }
    else if (trieAverage < hashAverage) {
        cout << "\nTrie was faster for this search." << endl;
    }
    else {
        cout << "\nBoth structures had the same average time." << endl;
    }

    if (hashResults.size() != trieResults.size()) {
        cout << "\nWarning: The two structures returned a different "
             << "number of results." << endl;
    }
}

// Displays the main menu.
void displayMenu() {
    cout << "\n====================================" << endl;
    cout << "       Song Autocomplete Finder" << endl;
    cout << "====================================" << endl;
    cout << "1. Search using Hash Table" << endl;
    cout << "2. Search using Trie" << endl;
    cout << "3. Compare Hash Table and Trie" << endl;
    cout << "4. Exit" << endl;
    cout << "====================================" << endl;
    cout << "Enter choice: ";
}

int main() {
    string filename = "dataset.csv";

    cout << "Loading song data..." << endl;

    vector<SearchEntry> songs =
        SongLoader::loadSongs(filename);

    if (songs.empty()) {
        cout << "Error: No song data was loaded." << endl;
        cout << "Make sure dataset.csv is in the correct folder."
             << endl;

        return 1;
    }

    cout << "Loaded " << songs.size()
         << " searchable entries." << endl;

    HashTable hashTable(200003);
    Trie trie;

    cout << "Building Hash Table and Trie..." << endl;

    for (const auto& entry : songs) {
        string key = entry.key;

        // Hash table needs every prefix inserted separately.
        for (size_t i = 1; i <= key.length(); i++) {
            string prefix = key.substr(0, i);
            hashTable.insert(prefix, entry.display);
        }

        // Trie only needs the full key inserted once.
        trie.insert(entry.key, entry.display);
    }

    cout << "Data structures built successfully." << endl;

    int choice;

    while (true) {
        displayMenu();

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Enter a number from 1 to 4."
                 << endl;

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        switch (choice) {
            case 1:
                runHashTableSearch(hashTable);
                break;

            case 2:
                runTrieSearch(trie);
                break;

            case 3:
                compareSearches(hashTable, trie);
                break;

            case 4:
                cout << "\nGoodbye!" << endl;
                return 0;

            default:
                cout << "\nInvalid choice. Enter a number "
                     << "from 1 to 4."
                     << endl;
        }
    }
}