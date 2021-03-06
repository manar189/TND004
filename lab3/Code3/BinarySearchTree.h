/************************************
* MEMBERS:                          *
*       M�ns Aronsson, manar189     *
*       Nisse Bergman, nisbe033     *
************************************/

#include <iostream>
#include <iomanip>  //setw
#include <utility>  //std::move

#pragma once

#include "dsexceptions.h"

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
    struct Node;  // nested class defined in node.h
    

public:

    class Iterator;
    

    Iterator begin() const
    {
        if (isEmpty()) return end();
        return Iterator(findMin(root));
	}

    Iterator end() const
    {
        return Iterator(nullptr);
	}


    BinarySearchTree() : root{nullptr} {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree &operator=(BinarySearchTree _copy) {
        std::swap(root, _copy.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    Iterator contains(const Comparable &x) const {
        
        //return (contains(x, root) != nullptr);     //Exercise 1
        return contains(x, root);     // Exercise 2

    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(ostream &out = cout) const {
        if (isEmpty()) {
            out << "Empty tree";
        } else {
            inorder(root, out);
            //preorder(root, out);
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty() {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x) {
        root = insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        root = remove(x, root);
    }

    /** Return total number of existing nodes
     *
     * Used for debug purposes
     */
    static int get_count_nodes() {
        return Node::count_nodes;
    }

    // get_parent in exercise 1
    const Comparable get_parent(const Comparable &x) const {
        Node* temp = contains(x, root);
        
        return (temp != nullptr && temp->parent != nullptr) ?
            temp->parent->element : Comparable{};
    }

    std::pair<Comparable, Comparable> find_pred_succ(const Comparable& x) const {
        std::pair<Comparable, Comparable> p;
        p.first = std::numeric_limits<Comparable>::min();
        p.second = std::numeric_limits<Comparable>::max();
        find_pred_succ(x, p, root);
        return p;
    }

private:
    Node *root;

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    Node *insert(const Comparable &x, Node *t) {
        if (t == nullptr) {
            t = new Node{x, nullptr, nullptr, nullptr};    
        } else if (x < t->element) {
            t->left = insert(x, t->left);
            t->left->parent = t;        // Our code
        } else if (t->element < x) {
            t->right = insert(x, t->right);
            t->right->parent = t;       // Our code
        } else {
            ;  // Duplicate; do nothing
        }

        return t;
    }


    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    Node *remove(const Comparable &x, Node *t) {
        if (t == nullptr) {
            return t;  // Item not found
        }
        if (x < t->element) {
            t->left = remove(x, t->left);
        } else if (t->element < x) {
            t->right = remove(x, t->right);
        }

        else if (t->left != nullptr && t->right != nullptr)  // Two children
        {
            // Answer to exc 4
            t->element = findMin(t->right)->element;
            t->right = remove(t->element, t->right);
        } else {    // One child
            Node *oldNode = t;

            // Left child
            if (t->left != nullptr) {
                t->left->parent = t->parent;
                t = t->left;
            }
            // Right child
            else if (t->right != nullptr) {
                t->right->parent = t->parent;
                t = t->right;
            }
            // Becomes nullptr if leaf
            else t = t->right;
            
            delete oldNode;
        }

        return t;
    }

    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    static Node *findMin(Node *t) {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }

        // Tail recursion can be easily replaced by a loop
        return findMin(t->left);  // recursive call
    }

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    static Node *findMax(Node *t) {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }

        return t;
    }

    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     */
    Node *contains(const Comparable &x, Node *t) const {
        if (t == nullptr) {
            return t;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return t;  // Match
        }
    }
    /****** NONRECURSIVE VERSION*************************
    Node *contains(const Comparable &x, Node *t) const {
        while (t != nullptr) {
            if (x < t->element) {
                t = t->left;
            } else if (t->element < x) {
                t = t->right;
            } else {
                return t;  // Match
            }
        }

        return t;  // No match
    }
    *****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    Node *makeEmpty(Node *t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }

        return nullptr;
    }

    /**
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void inorder(Node *t, ostream &out) const {
        if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }
    }

    void preorder(Node *t, ostream &out, int spaces = 0) const {
        if(t != nullptr) {
            
            for (int i = 0; i <= spaces; ++i) {
                out << " ";
            }
            out << t->element << '\n';

            preorder(t->left, out, spaces + 2);
            preorder(t->right, out, spaces + 2);
		}
	}

    /**
     * Private member function to clone subtree.
     */
    Node *clone(Node *t) const {
        if (t == nullptr) {
            return nullptr;
        } else {
            return new Node{t->element, clone(t->left), clone(t->right), t->parent};
        }
    }

    void find_pred_succ(const Comparable& x, std::pair<Comparable, Comparable>& p, Node* t) const {

        if (t != nullptr) {

            // Going down tree
            if (t->element < x) {

                p.first = t->element;
                find_pred_succ(x, p, t->right);

                if (p.first == x && t->element < p.first) {
                    p.first = t->element;
                }
                if (p.second == x && t->element > p.second) {
                    p.second = t->element;
                }

            }
            else if (x < t->element) {

                p.second = t->element;
                find_pred_succ(x, p, t->left);

                if (p.first == x && t->element < p.first) {
                    p.first = t->element;
                }
                if (p.second == x && t->element > p.second) {
                    p.second = t->element;
                }
            }
            // x is in tree
            else {
                //auto predPtr = find_predecessor(t);
                //auto sucPtr = find_successor(t); // if right subtree, findmax     if left subtree, findmin

                auto minPtr = findMax(t->left);
                auto maxPtr = findMin(t->right);

                // Only one node
                if (minPtr == nullptr && maxPtr == nullptr) {
                    p.first = x;
                    p.second = x;
                    return;
                }
                // No predecessor
                if (minPtr == nullptr) {
                    p.first = x;
                    p.second = maxPtr->element;
                    return;
                }
                // No successor
                if (maxPtr == nullptr) {
                    p.first = minPtr->element;
                    p.second = x;
                    return;
                }
                
                // Has both predecessor and successor
                p.first = minPtr->element;
                p.second = maxPtr->element;
                
            }
        }
    }

    static Node* find_predecessor(Node* t) {

        if (t != nullptr && t->left != nullptr){
            return findMax(t->left); 
        } 
        else //predecessor is one of the ancestors 
        { 

            while (t->parent != nullptr && t == t->parent->left) {

                t = t->parent;
            }

            return t->parent;
        }
    }

    static Node* find_successor(Node* t) {

        if (t != nullptr && t->right) {
            return findMin(t->right);
        }
        else //successor is one of the ancestors 
        {

            while (t->parent != nullptr && t == t->parent->right) {

                t = t->parent;
            }

            return t->parent;
        }
    }


};

//Include the definition of class Node
#include "node.h"
#include "iterator.h"