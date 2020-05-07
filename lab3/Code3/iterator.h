/************************************
* MEMBERS:                          *
*       Måns Aronsson, manar189     *
*       Nisse Bergman, nisbe033     *
************************************/
#include "BinarySearchTree.h"

#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
private:
    friend class BinarySearchTree<Comparable>;

public:

    Iterator();

    Comparable& operator*() const {
        return current->element;
    };

    Comparable* operator->() const {
        return current;
    };

    bool operator==(const Iterator& it) const {
        return (current == it.current);
    };

    bool operator!=(const Iterator& it) const {
        return (!(current == it.current));
    };

    Iterator& operator++() {    //pre-increment
        
        current = find_successor(current);
        return *this;
    
    };

    Iterator operator++(int) {  // pos-increment
        Iterator temp{*this};
        ++(*this);
        return temp;
    }

    Iterator& operator--() { //pre-decrement
        current = find_predecessor(current);
        return *this;
    }; 

    Iterator operator--(int) {  // pos-decrement
        Iterator temp{ *this };
        --(*this);
        return temp;
    }

   

private:
    Node* current;
    Iterator(Node* p = nullptr) : current{ p } { }

};
