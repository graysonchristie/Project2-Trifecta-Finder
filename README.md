# Project2-Trifecta-Finder

## Project Description
The Trifecta Finder is a music autocomplete program. It compares a custom Trie and a custom Hash Table using a Spotify dataset with about 114,000 tracks.

## Team Members
- Grayson Christie
- Zachary Bosworth
- Isabella Tarsitano

## Files
- `main.cpp` - Runs the main program and connects the dataset, Trie, and Hash Table.
- `SongLoader.h` - Loads the Spotify CSV file and formats entries as `Artist - Song Title`.
- `Trie.h` - Custom Trie implementation.
- `HashTable.h` - Custom Hash Table implementation.
- `dataset.csv` - Spotify tracks dataset.
- `CMakeLists.txt` - CMake/CLion build file.

## How to Run in CLion
1. Clone or download this GitHub repository.
2. Open the project folder in CLion.
3. Make sure `dataset.csv` is in the main project folder.
4. Build and run `main.cpp`.
5. Follow the console menu prompts.

## Current Dataset Format
The program loads the dataset into a vector of strings.

Each entry is formatted as:

`Artist - Song Title`

Example:

`Taylor Swift - Blank Space`

## Notes
The Trie and Hash Table are implemented from scratch for this project.