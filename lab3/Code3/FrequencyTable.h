/************************************
* MEMBERS:                          *
*       Måns Aronsson, manar189     *
*       Nisse Bergman, nisbe033     *
************************************/
#include <string>
#include "BinarySearchTree.h" 

class FrequencyTable {

public:
    FrequencyTable(string i, int n = 1) : key{ i }, counter{ n } { }

    bool operator<(const FrequencyTable& f) const {
        return (key < f.key);
    }

    FrequencyTable& operator++() {
        ++(*this).counter;
        return (*this);
    }

    friend ostream& operator<<(ostream& os, const FrequencyTable& rhs);

private:

    string key;
    int counter;

};

ostream& operator<<(ostream& os, const FrequencyTable& rhs) {
    os << std::setw(20) << std::left << rhs.key;
    os << std::setw(10) << std::right << std::to_string(rhs.counter);
    return os;
}