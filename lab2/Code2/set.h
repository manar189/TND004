#include <iostream>
#include <vector>

#pragma once

/** Class to represent a Set of ints
 *
 * Set is implemented as a sorted doubly linked list
 * Sets should not contain repetitions, i.e.
 * two ints with the same value cannot belong to a Set
 *
 * All Set operations must have a linear complexity, in the worst case
 */
class Set {

public:
    // Default constructor: create an empty Set
    // IMPLEMENT before HA session on week 16
    Set();

    // Conversion constructor: Convert val into a singleton {val}
    // IMPLEMENT before HA session on week 16
    Set(int val);

    /** Constructor to create a Set from a sorted vector of ints
     *
     * Create a Set with all ints in sorted vector v
     * \param v sorted vector of ints
     *
     */
    // IMPLEMENT before HA session on week 16
    Set(const std::vector<int>& v);

    /** Copy constructor
     *
     * Create a new Set as a copy of Set b
     * \param b Set to be copied
     * Function does not modify Set b in any way
     *
     */
    // IMPLEMENT before HA session on week 16
    Set(const Set& b);

    /** Destructor
     *
     * Deallocate all memory (Nodes) allocated by the constructor
     *
     */
    // IMPLEMENT before HA session on week 16
    ~Set();

    /** Assignment operator
     *
     * Assigns new contents to the Set, replacing its current content
     * \param source Set to be copied into Set *this
     * Call by valued is used. Thus, this function works also as move assignment operator
     *
     */
    // IMPLEMENT before HA session on week 16
    Set& operator=(Set source);

    /** Test whether the Set is empty
     *
     * This function does not modify the Set in any way
     * Return true if the set is empty, otherwise false
     *
     */
    bool is_empty() const;

    /** Count the number of values stored in the Set
     *
     * This function does not modify the Set in any way
     * Return number of elements in the set
     *
     */
    size_t cardinality() const;

    /** Test whether val belongs to the Set
     *
     * This function does not modify the Set in any way
     * Return true if val belongs to the set, otherwise false
     *
     */
    // IMPLEMENT before HA session on week 16
    bool is_member(int val) const;

    /** Transform the Set into an empty se
     *
     * Remove all nodes from the list, except the dummy nodes
     *
     */
    // IMPLEMENT before HA session on week 16
    void make_empty();

    /** Test whether Set *this is a subset of Set b
     *
     * a <= b iff every member of a is a member of b
     * Function does not modify *this nor b in any way
     * Return true, if *this is a subset of b, otherwise false
     *
     */
    // IMPLEMENT
    bool operator<=(const Set& b) const;

    /** Test whether Set *this and b represent the same set
     *
     * a == b, iff a <= b but not b <= a
     * Function does not modify *this nor b in any way
     * Return true, if *this stores the same elements as Set b, otherwise false
     *
     */
    // IMPLEMENT
    bool operator==(const Set& b) const;

    /** Test whether Set *this and b represent different sets
     *
     * a != b, iff (a==b) is false
     * Function does not modify *this nor b in any way
     * Return true, if *this stores the same elements as Set b, otherwise false
     *
     */
    // IMPLEMENT
    bool operator!=(const Set& b) const;

    /** Test whether Set *this is a strict subset of Set b
     *
     * a < b iff a <= b but not b <= a
     * Function does not modify *this nor b in any way
     * Return true, if *this is a strict subset of b, otherwise false
     */
    // IMPLEMENT
    bool operator<(const Set& b) const;

    /** Return number of existing nodes
     *
     * Used for debug purposes
     */

    /** Modify Set *this such that it becomes the union of *this with Set S
     *
     * Set *this is modified and then returned
     *
     */
    // IMPLEMENT
    Set& operator+=(const Set& S);

    /** Modify Set *this such that it becomes the intersection of *this with Set S
     *
     * Set *this is modified and then returned
     *
     */
    // IMPLEMENT
    Set& operator*=(const Set& S);

    /** Modify Set *this such that it becomes the Set difference between Set *this and Set S
     *
     * Set *this is modified and then returned
     *
     */
    // IMPLEMENT
    Set& operator-=(const Set& S);

    /** Return number of existing nodes in the current program
     *
     * Used for debug purposes
     *
     */
    static int get_count_nodes();

private:
    class Node;  // nested class defined in file node.h

    Node* head;      // Pointer to the dummy header Node
    Node* tail;      // Pointer to the dummy tail Node
    size_t counter;  // number of values in the Set

    /* ***************************** *
     * Overloaded Global Operators   *
     * ***************************** */

    /** Overloaded operator<<
     *
     * \param os ostream object where the set b elements are written
     *
     */
    friend std::ostream& operator<<(std::ostream& os, const Set& b);

    /** Overloaded operator+: Set union S1+S2
     *
     * S1+S2 is the Set of elements in Set S1 or in Set S2 (without repeated elements)
     * Function does not modify S2 in any way
     * Return a new Set representing the union of S1 with S2, S1+S2
     *
     */
    friend Set operator+(Set S1, const Set& S2) {
        return (S1 += S2);
    }

    /** Overloaded operator*: Set intersection S1*S2
     *
     * S1*S2 is the Set of elements in both Sets S1 and set S2
     * Return a new Set representing the intersection of S1 with S2, S1*S2
     *
     */
    friend Set operator*(Set S1, const Set& S2) {
        return (S1 *= S2);
    }

    /** Overloaded operator-: Set difference S1-S2
     *
     * S1-S2 is the Set of elements in Set S1 that do not belong to Set S2
     * Return a new Set representing the set difference S1-S2
     *
     */
    friend Set operator-(Set S1, const Set& S2) {
        return (S1 -= S2);
    }
};