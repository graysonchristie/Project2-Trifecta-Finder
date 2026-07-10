#ifndef PROJECT2_TRIFECTA_FINDER_SONGLOADER_H
#define PROJECT2_TRIFECTA_FINDER_SONGLOADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// One searchable version of a track
struct SearchEntry {
    string key;      // Text inserted/searched in Trie or Hash Table
    string display;  // Text shown to the user
};

class SongLoader {
private:
    // Splits a CSV row while keeping commas inside quotes together.
    static vector<string> splitCSVLine(const string& line) {
        vector<string> columns;
        string current;
        bool inQuotes = false;

        for (char c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
            }
            else if (c == ',' && !inQuotes) {
                columns.push_back(current);
                current.clear();
            }
            else {
                current += c;
            }
        }

        columns.push_back(current);
        return columns;
    }

    // Removes unnecessary spaces and surrounding quotes.
    static string cleanString(string text) {
        while (!text.empty() && text.front() == ' ') {
            text.erase(text.begin());
        }

        while (!text.empty() && text.back() == ' ') {
            text.pop_back();
        }

        if (text.size() >= 2 &&
            text.front() == '"' &&
            text.back() == '"') {

            text = text.substr(1, text.size() - 2);
        }

        return text;
    }

public:
    static vector<SearchEntry> loadSongs(const string& filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Could not open dataset file: "
                 << filename << endl;

            return {};
        }

        vector<SearchEntry> entries;

        // Prevent duplicate searchable records.
        set<string> seen;

        string line;

        // Skip CSV header.
        getline(file, line);

        while (getline(file, line)) {
            vector<string> columns = splitCSVLine(line);

            /*
             Parsed dataset columns:

             1 = unnamed row index
             2 = track_id
             3 = artists
             4 = album_name
             5 = track_name
            */

            if (columns.size() > 5) {
                string artist = cleanString(columns[3]);
                string song = cleanString(columns[5]);

                if (!artist.empty() && !song.empty()) {
                    string display = artist + " - " + song;

                    // Artist-search version
                    string artistRecord = artist + "|" + display;

                    if (seen.insert(artistRecord).second) {
                        entries.push_back({artist, display});
                    }

                    // Song-search version
                    string songRecord = song + "|" + display;

                    if (seen.insert(songRecord).second) {
                        entries.push_back({song, display});
                    }
                }
            }
        }

        file.close();
        return entries;
    }
};


#endif //PROJECT2_TRIFECTA_FINDER_SONGLOADER_H