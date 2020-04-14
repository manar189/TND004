#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

// Used for debug purposes
// Return number of existing nodes
int Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

// Default constructor
Set::Set() : counter{0} {
    // IMPLEMENT before HA session on week 16
    
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

// Conversion constructor
Set::Set(int n)
    : Set{}  // create an empty list
{
    // IMPLEMENT before HA session on week 16
    Node* newNode = new Node(n, tail, head);
    head->next = newNode;
    tail->prev = newNode;
    ++counter;
}

// Constructor to create a Set from a sorted vector v
Set::Set(const std::vector<int>& v)
    : Set{}  // create an empty list
{
    // IMPLEMENT before HA session on week 16
    auto it = v.begin();
    Node* temp = head;

    while (it != v.end())
    {
        Node* newNode = new Node(*it, temp->next, temp);
        temp->next = newNode;
        tail->prev = newNode;
        temp = temp->next;
        ++counter;
        ++it;
    }

}

// Make the set empty
void Set::make_empty() {
    // IMPLEMENT before HA session on week 16
    Node* ptr = head->next;
    
    while (ptr != tail)
    {
        Node* temp = ptr;
        ptr = ptr->next;
        --counter;
        delete temp;
    }

    head->next = tail;
    tail->prev = head;
}

Set::~Set() {
    // Member function make_empty() can be used to implement the destructor
    // IMPLEMENT before HA session on week 
    make_empty();
    delete head;
    delete tail;
}

// Copy constructor
Set::Set(const Set& source)
    : Set{}  // create an empty list
{
    // IMPLEMENT before HA session on week 16
    Node* ptrSource = source.head->next;
    Node* ptrOrg = head;

    while (ptrSource != source.tail)
    {
        Node* temp = new Node(ptrSource->value, ptrOrg->next, ptrOrg);
        ptrOrg->next = temp;
        tail->prev = temp;
        ptrOrg = ptrOrg->next;
        ++counter;

        ptrSource = ptrSource->next;
    }
}

// Copy-and-swap assignment operator
Set& Set::operator=(Set source) {
    // IMPLEMENT before HA session on week 16
    Set _copy{ source };
    std::swap(head, _copy.head);
    std::swap(tail, _copy.tail);
    std::swap(counter, _copy.counter);
   
    return *this;
}

// Test whether a set is empty
bool Set::is_empty() const {
    return (counter == 0);
}

// Test set membership
bool Set::is_member(int val) const {
    // IMPLEMENT before HA session on week 16
    Node* ptr = head->next;
    while (ptr != tail)
    {
        if (ptr->value == val)
            return true;

        ptr = ptr->next;
    }

    return false;
}

// Return number of elements in the set
size_t Set::cardinality() const {
    return counter;
}

// Return true, if the set is a subset of b, otherwise false
// a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const {
    // IMPLEMENT
    Node* ptrOrg = head->next;
    Node* ptrB = b.head->next;
    while (ptrOrg != tail && ptrB != b.tail)
    {
        if (ptrOrg->value < ptrB->value)
            return false;

        if (ptrOrg->value == ptrB->value)
        {
            ptrOrg = ptrOrg->next;
            ptrB = ptrB->next;
        }
        else
        {
            ptrB = ptrB->next;
        }
    }

    return(ptrOrg == tail);
}

// Return true, if the set is equal to set b
// a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const {

    return ( *this <= b && b <= *this);
}

// Return true, if the set is different from set b
// a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const {

    return !(*this == b);
}

// Return true, if the set is a strict subset of S, otherwise false
// a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const {
    
    return (*this <= b && this->counter < b.counter);
}

// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {
    
    Node* ptrOrg = head->next;
    Node* ptrS = S.head->next;

    while (ptrOrg != tail && ptrS != S.tail) {

        if (ptrOrg->value < ptrS->value) {
            ptrOrg = ptrOrg->next;
        }
        else if (ptrOrg->value == ptrS->value) {
            ptrOrg = ptrOrg->next;
            ptrS = ptrS->next;

        }
        else if (ptrOrg->value > ptrS->value) {
            Node* newNode = new Node(ptrS->value, ptrOrg, ptrOrg->prev);
            
            ptrOrg->prev->next = newNode;
            ptrOrg->prev = newNode;

            ptrS = ptrS->next;
            ++counter;
        }
	}

    while (ptrS != S.tail) {
        Node* newNode = new Node(ptrS->value, ptrOrg, ptrOrg->prev);

        ptrOrg->prev->next = newNode;
        tail->prev = newNode;

        ptrS = ptrS->next;
        ++counter;
    }

    return *this;
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {
    Node* ptrOrg = head->next;
    Node* ptrS = S.head->next;

    while (ptrOrg != tail && ptrS != S.tail) {

        if (ptrOrg->value < ptrS->value) {
            ptrOrg->prev->next = ptrOrg->next;
            ptrOrg->next->prev = ptrOrg->prev;

            Node* temp = ptrOrg;
            ptrOrg = ptrOrg->next;

            delete temp;
            --counter;
        }
        else if (ptrOrg->value == ptrS->value) {
            ptrOrg = ptrOrg->next;
            ptrS = ptrS->next;

        }
        else if (ptrOrg->value > ptrS->value) {
            ptrS = ptrS->next;
        }
    }

    while (ptrOrg != tail) {
        ptrOrg->prev->next = ptrOrg->next;
        ptrOrg->next->prev = ptrOrg->prev;

        Node* temp = ptrOrg;
        ptrOrg = ptrOrg->next;

        delete temp;
        --counter;
    }

    return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {
    Node* ptrOrg = head->next;
    Node* ptrS = S.head->next;

    while (ptrOrg != tail && ptrS != S.tail) {

        if (ptrOrg->value < ptrS->value) {
            ptrOrg = ptrOrg->next;
        }
        else if (ptrOrg->value == ptrS->value) {
            ptrOrg->prev->next = ptrOrg->next;
            ptrOrg->next->prev = ptrOrg->prev;

            Node* temp = ptrOrg;
            ptrOrg = ptrOrg->next;
            ptrS = ptrS->next;

            delete temp;
            --counter;
        }
        else if (ptrOrg->value > ptrS->value) {
            ptrS = ptrS->next;
        }
    }

    /*while (ptrS != S.tail) {
        Node* newNode = new Node(ptrS->value, ptrOrg, ptrOrg->prev);

        ptrOrg->prev->next = newNode;
        tail->prev = newNode;

        ptrS = ptrS->next;
        ++counter;
    }*/

    return *this;
}

// Overloaded stream insertion operator<<
std::ostream& operator<<(std::ostream& os, const Set& b) {
    if (b.is_empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp{b.head->next};

        os << "{ ";
        while (temp != b.tail) {
            os << temp->value << " ";
            temp = temp->next;
        }

        os << "}";
    }

    return os;
}

/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

//If you add any private member functions to class Set then write the implementation here


