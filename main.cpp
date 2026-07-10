#include <iostream>
#include <vector>
#include <string>
#include "SongLoader.h"

using namespace std;

int main() {
    string filename =
        "C:/Users/gchri/CLionProjects/Project2-Trifecta-Finder/dataset.csv";

    vector<SearchEntry> songs = SongLoader::loadSongs(filename);

    cout << "Loaded search entries: " << songs.size() << endl;

    cout << "\nFirst 10 entries:\n";
    for (int i = 0; i < 10 && i < songs.size(); i++) {
        cout << i + 1
             << ". Key: " << songs[i].key
             << " | Display: " << songs[i].display
             << endl;
    }

    string target = "Olivia Rodrigo";
    int found = 0;

    cout << "\nSearching for: " << target << endl;

    for (int i = 0; i < songs.size() && found < 10; i++) {
        if (songs[i].key.find(target) != string::npos) {
            cout << found + 1 << ". " << songs[i].display << endl;
            found++;
        }
    }

    cout << "Matches found shown: " << found << endl;

    return 0;
}