/************************************
* MEMBERS:                          *
*       Måns Aronsson, manar189     *
*       Nisse Bergman, nisbe033     *
************************************/
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <cassert>    //assert
#include <algorithm>  //std::sort
#include <string>

#include "vld.h"
#include "BinarySearchTree.h"
#include "FrequencyTable.h"
   
int main() {

    BinarySearchTree<FrequencyTable> tree;

    //std::ifstream file{ "../../other_files/text.txt" };
    std::ifstream file{ "../../other_files/text_long.txt" };

    if (!file) {
        cout << "Could not open file" << endl;
        return 1;
    }

    vector<string> V = { std::istream_iterator<string>{file}, std::istream_iterator<string>{} };

    file.close();

    for (auto word : V) {

        size_t old, _new;
        for (old = 0, _new = 0; old < word.size(); ++old) {
            
            if (!ispunct(static_cast<unsigned char>(word[old])) || isdigit(word[old]) || word[old] == '\'' ) {
                word[_new] = tolower(word[old]);
                ++_new;
            }
        }
        word.erase(_new, old - _new);
        
        auto it = tree.contains(word);
        if (it != tree.end()) {
            ++*it;

        }
        else {
            tree.insert(word);
        }
    }

    for (auto it = tree.begin(); it != tree.end(); ++it) { cout << *it << endl; }    

    return 0;
}

