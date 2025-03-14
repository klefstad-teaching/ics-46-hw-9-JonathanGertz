#include "ladder.h"
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void test_word_ladder() {
    set<string> word_list = {"cat", "bat", "hat", "bad", "had", "bag", "rag", "rat", "ragged"};
    
    string start = "cat";
    string end = "rag";
    
    vector<string> ladder = generate_word_ladder(start, end, word_list);
    
    cout << "Testing word ladder from '" << start << "' to '" << end << "':\n";
    print_word_ladder(ladder);
    verify_word_ladder();
}

int main() {
    test_word_ladder();
    return 0;
}
