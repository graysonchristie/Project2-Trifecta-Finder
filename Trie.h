//
// Created by gchri on 7/10/2026.
//

#ifndef PROJECT2_TRIFECTA_FINDER_TRIE_H
#define PROJECT2_TRIFECTA_FINDER_TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    TrieNode(){
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};




#endif //PROJECT2_TRIFECTA_FINDER_TRIE_H