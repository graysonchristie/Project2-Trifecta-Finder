#ifndef PROJECT2_TRIFECTA_FINDER_SONGLOADER_H
#define PROJECT2_TRIFECTA_FINDER_SONGLOADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SongLoader {
private:
    // Splits a CSV line while respecting quotes.
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

    // Basic cleanup for weird spacing/quotes.
    static string cleanString(string text) {
        while (!text.empty() && text.front() == ' ') {
            text.erase(text.begin());
        }

        while (!text.empty() && text.back() == ' ') {
            text.pop_back();
        }

        if (text.size() >= 2 && text.front() == '"' && text.back() == '"') {
            text = text.substr(1, text.size() - 2);
        }

        return text;
    }

public:
    static vector<string> loadSongs(const string& filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Could not open dataset file: " << filename << endl;
            return {};
        }

        vector<string> entries;
        string line;

        // Skip header row
        getline(file, line);

        while (getline(file, line)) {
            vector<string> columns = splitCSVLine(line);

            /*
             Dataset columns:
             1 = unnamed index
             2 = track_id
             3 = artists
             4 = album_name
             5 = track_name
            */

            if (columns.size() > 5) {
                string artist = cleanString(columns[3]);
                string song = cleanString(columns[5]);

                if (!artist.empty() && !song.empty()) {
                    string entry = artist + " - " + song;
                    entries.push_back(entry);
                }
            }
        }

        file.close();
        return entries;
    }
};

#endif //PROJECT2_TRIFECTA_FINDER_SONGLOADER_H