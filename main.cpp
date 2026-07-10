#include <iostream>
#include <vector>
#include <string>
#include "SongLoader.h"

using namespace std;

int main() {
    string filename = "C:/Users/gchri/CLionProjects/Project2-Trifecta-Finder/dataset.csv";

    vector<string> songs = SongLoader::loadSongs(filename);

    cout << "Loaded song entries: " << songs.size() << endl;

    cout << "\nFirst 10 entries:\n";
    for (int i = 0; i < 10 && i < songs.size(); i++) {
        cout << i + 1 << ". " << songs[i] << endl;
    }

    return 0;
}