#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <cassert>    //assert
#include <algorithm>  //std::sort
#include <string>

#include "BinarySearchTree.h"
#include "iterator.h"

int main() {
    {
        std::ifstream file{"../../other_files/words.txt"};

        if (!file) {
            std::cout << "Couldn't open file words.txt\n";
            return 1;
        }

        std::vector<std::string> V{std::istream_iterator<string>{file},
                                   std::istream_iterator<string>{}};
        file.close();

        // Create a tree
        BinarySearchTree<std::string> t;
        assert(BinarySearchTree<std::string>::get_count_nodes() == 0);

        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<std::string>::get_count_nodes() == 35);

        // Display the tree
        /*std::cout << "Tree: \n";
        t.printTree();
        std::cout << '\n';*/

        // Load the expected inorder traversal of the tree
        file.open("../../other_files/inorder_traversal.txt");

        if (!file) {
            std::cout << "Couldn't open file inorder_traversal.txt\n";
            return 1;
        }

        std::vector<std::string> inorder{std::istream_iterator<string>{file},
                                         std::istream_iterator<string>{}};
        file.close();

        /**************************************/
        std::cout << "\nPHASE 0: contains\n";
        /**************************************/
        {
            // some words in the tree
            std::vector<std::string> V1{"airborne", "yelp", "obligations", "unbridled"};

            for (auto w : V1) {
                assert(*t.contains(w) == w);
            }

            std::vector<std::string> V2{"stop", "Sweden"};

            // some words not in the tree
            for (auto w : V2) {
                assert(t.contains(w) == t.end());
            }
        }

        /****************************************************/
        std::cout << "\nPHASE 1: operator++, operator*\n";
        /****************************************************/
        {
            std::vector<std::string> V1{};

            // Inorder traversal
            /* for (BinarySearchTree<string>::Iterator it = t.begin(); it != t.end(); ++it) {
                 V1.push_back(*it);
             }*/

            // Inorder traversal
            for (auto w : t) {
                V1.push_back(w);
            }

            assert(V1 == inorder);
        }

        /****************************************************/
        std::cout << "\nPHASE 2: operator--, operator*\n";
        /*****************************************************/
        {
            std::string largest{t.findMax()};

            assert(largest == "yelp");

            std::vector<std::string> V1{};

            // Backwards inorder traversal
            for (auto it = t.contains(largest); it != t.end(); --it) {
                V1.push_back(*it);
            }

            std::sort(V1.begin(), V1.end());
            assert(V1 == inorder);
        }
    }

    assert(BinarySearchTree<std::string>::get_count_nodes() == 0);
    std::cout << "\nSuccess!!\n";

    return 0;
}
