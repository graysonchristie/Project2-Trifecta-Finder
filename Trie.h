#ifndef PROJECT2_TRIFECTA_FINDER_TRIE_H
#define PROJECT2_TRIFECTA_FINDER_TRIE_H

#include <cctype>
#include <set>
#include <string>
#include <vector>

// ----------- Information about SongLoader.h -----------
// the only thing ever recieved from Song Loader is a vector of songs --> vector<SearchEntry> songs;
/* there are two entries:
    - Artist searching: Key -> Artist Name, Display -> "Key - Song"
    - Song Searching: Key -> Song, Display -> "Key - Song"

So we'll be storing the key, and returning the display essentially. (entry.key, entry.display)
*/

// ----------- Information about main.cpp -----------
/*
Eventually they'll need something like this:

        ----------- trie.insert() -----------
Trie trie;
for (const auto& entry : songs) {
    trie.insert(entry.key, entry.display);
}

They'll essentially just need ONE insertion, as the Trie itself already represents prefixes.
eg., for main.cpp:
    trie.search("Rad"); --> and the trie will essentially search through its containers.

----------- trie.search() -----------
Meaning, what search expects is a vector<string> to be returned from trie.search()

It'll find all the keys that start with said prefix, and then return their display strings.
*/

using namespace std;

struct TrieNode {
    TrieNode* children[256];
    bool isEndOfWord;
    vector<string> displays; // display strings that end EXACTLY at this node

    TrieNode() {
        isEndOfWord = false;

        for (int i = 0; i < 256; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

    // Converts text to lowercase so searching is not case-sensitive.
    string toLower(string text) const {
        for (char& c : text) {
            c = static_cast<char>(
                tolower(static_cast<unsigned char>(c))
            );
        }

        return text;
    }

    // Implementing a Depth-First Search (DFS) Algorithm here to check EVERY path
    // Upon finding the node, DFS will ADD the node when the node is MARKED as 'isEndOfWord'
    // and during insertion it was marked, it'll be added to the list of display strings.
    void collectAll(TrieNode* node, set<string>& results) const {
        if (node == nullptr) {
            return;
        }

        if (node->isEndOfWord) {
            for (const string& display : node->displays) {
                results.insert(display);
            }
        }

        for (int i = 0; i < 256; i++) {
            collectAll(node->children[i], results);
        }
    }

    // Delete EVERY node so there are no memory leaks.
    void destroy(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < 256; i++) {
            destroy(node->children[i]);
        }

        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        destroy(root);
    }

    // Prevent accidental copying because the Trie owns dynamic memory.
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Insert a SINGLE key (song title or artist name) INTO the PREFIX TREE (which is our Trie).
    void insert(const string& key, const string& display) {
        string normalizedKey = toLower(key);

        TrieNode* current = root;

        for (char c : normalizedKey) {
            unsigned char index =
                static_cast<unsigned char>(c);

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->isEndOfWord = true; // MARKED.
        current->displays.push_back(display);
    }

    // Traverses down the trie one character at a time, while MATCHING the prefix characters
    // After implementing the DFS or finishing the prefix loop, you will have reached the subtree's root or the prefix's node,
    // and you will send this node into a recursive HELPER function to gather EVERY SONG BELOW IT.
    vector<string> search(const string& prefix) const {
        string normalizedPrefix = toLower(prefix);

        TrieNode* current = root;

        for (char c : normalizedPrefix) {
            unsigned char index =
                static_cast<unsigned char>(c);

            if (current->children[index] == nullptr) {
                return {}; // NOTHING in the trie started with this prefix
            }

            current = current->children[index];
        }

        set<string> resultSet; // Gets auto sorted in alphabetical order and is free of duplicates.
        collectAll(current, resultSet);

        return vector<string>(
            resultSet.begin(),
            resultSet.end()
        );
    }
};

#endif // PROJECT2_TRIFECTA_FINDER_TRIE_H