#include <chrono>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <cctype>

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

    cout << "\nHash-table search time: "
         << searchTime.count()
         << " nanoseconds" << endl;
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

    // Create the hash table.
    HashTable hashTable(200003);

    cout << "Building hash table..." << endl;

    // Insert every prefix from each artist or song key.
    for (const auto& entry : songs) {
        string key = entry.key;

        for (size_t i = 1; i <= key.length(); i++) {
            string prefix = key.substr(0, i);

            hashTable.insert(prefix, entry.display);
        }
    }

    cout << "Hash table built successfully." << endl;

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
                cout << "\nTrie search is not available yet."
                     << endl;
                break;

            case 3:
                cout << "\nComparison is not available until "
                     << "the Trie is added."
                     << endl;
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