#include <iostream>
#include <vector>
#include <string>
#include "SongLoader.h"
#include "SongLoader.h"
#include "HashTable.h"


using namespace std;

int main() {/*
    string filename =
        "C:/Users/gchri/CLionProjects/Project2-Trifecta-Finder/dataset.csv";

    vector<SearchEntry> songs = SongLoader::loadSongs(filename);

    cout << "Loaded search entries: " << songs.size() << endl;

    string target = "Olivia Rodrigo";
    int found = 0;

    cout << "\nSearching for: " << target << endl;

    for (int i = 0; i < songs.size() && found < 10; i++) {
        if (songs[i].key.find(target) != string::npos) {
            cout << found + 1 << ". " << songs[i].display << endl;
            found++;
        }
    }

    cout << "Matches found shown: " << found << endl; */
    string filename = "/Users/kentarsitano/Desktop/COP3530/Project2-Trifecta-Finder3/dataset.csv";

    // Load songs using SearchEntry
    vector<SearchEntry> songs = SongLoader::loadSongs(filename);
    cout << "Loaded " << songs.size() << " searchable entries." << endl;

    // Init Hash
    HashTable ht(200003);

    // Populate Hash Table using the 'key' (either Artist or Song Title)
    cout << "Populating Hash Table with prefixes from keys..." << endl;
    for (const auto& entry : songs) {
        // entry.key -> index the prefix
        // entry.display -> the value
        string key = entry.key;
        for (size_t i = 1; i <= key.length(); ++i) {
            string prefix = key.substr(0, i);
            ht.insert(prefix, entry.display);
        }
    }
    cout << "Hash Table populated successfully!" << endl;

    // Testing Hash Search Functionality
    // Swap to test both artist and song title
    vector<string> testQueries = {"Olivia Rodrigo", "Creep"};

    for (const string& query : testQueries) {
        cout << "\nTesting search for: \"" << query << "\"" << endl;

        vector<string> results = ht.search(query);

        if (results.empty()) {
            cout << "No matches found." << endl;
        } else {
            cout << "Found " << results.size() << " matches:" << endl;
            // Print 5 results
            for (int i = 0; i < results.size() && i < 5; ++i) {
                cout << "  - " << results[i] << endl;
            }
        }
    }

    return 0;
}