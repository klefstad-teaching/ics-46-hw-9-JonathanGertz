#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > d) return false;
    
    int i = 0, j = 0, edits = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++edits > d) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return edits + (len1 - i) + (len2 - j) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladders;
    set<string> visited;
    ladders.push({begin_word});
    visited.insert(begin_word);
    
    while (!ladders.empty()) {
        int size = ladders.size();
        set<string> this_level_visited;
        
        for (int i = 0; i < size; i++) {
            vector<string> path = ladders.front();
            ladders.pop();
            string last_word = path.back();
            
            if (last_word == end_word) return path;
            
            for (const string& word : word_list) {
                if (!visited.count(word) && is_adjacent(last_word, word)) {
                    vector<string> new_path = path;
                    new_path.push_back(word);
                    ladders.push(new_path);
                    this_level_visited.insert(word);
                }
            }
        }
        for (const string& word : this_level_visited) {
            visited.insert(word);
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No transformation sequence found." << endl;
        return;
    }
    cout << "Word Ladder: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " -> ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    string start, end;
    cout << "Enter start word: ";
    cin >> start;
    cout << "Enter end word: ";
    cin >> end;
    
    vector<string> ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);
}
