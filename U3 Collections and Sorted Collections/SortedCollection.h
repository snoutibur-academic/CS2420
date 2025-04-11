#ifndef SORTEDCOLLECTION_H
#define SORTEDCOLLECTION_H

#include "Collection.h"
#include <memory>

template<typename Item>
class SortedCollection : public Collection<Item> {
    public:
    // Constructors x3 overloaded no/int/given collection
    SortedCollection();
    SortedCollection(int size);
    SortedCollection(Collection<Item> &a);

    // Overload add method
    virtual void add(Item e);

    // Additional overloaded + Operator
    virtual SortedCollection<Item> &operator+(Item e);

    // Additional overloaded << operator
    SortedCollection<Item> &operator<< (Item in);
};

// CONSTRUCTORS
template<typename Item>
SortedCollection<Item>::SortedCollection() : Collection<Item>::Collection() {}

template<typename Item>
SortedCollection<Item>::SortedCollection(int size) : Collection<Item>::Collection(size) {}

template<typename Item>
SortedCollection<Item>::SortedCollection(Collection<Item> &a) : Collection<Item>::Collection(a) {
    // unique_ptr<Item[]> arr = make_unique<Item[]>(a.size());
    // for(int i = 0; i < a.size(); i++) {
    //      add(a.get(i));
    // }
}

// Overloaded add method: USE INSERTION SORT
template<typename Item>
void SortedCollection<Item>::add(Item e) {
    // Overflow protection
    // if (Collection<Item>::curSize == Collection<Item>::capacity) {
        // Collection<Item>::expand();
        Collection<Item>::add(e);
    // }

    // Find where to insert & make space for the insert
    int i = Collection<Item>::size() -1;
    while ((i > 0) && (Collection<Item>::get(i-1) > e)) {
        Collection<Item>::elements[i] = Collection<Item>::elements[i-1]; // Copies index to the next spot
        Collection<Item>::elements[i-1] = e; // Puts input where it should be
        i--;; // Move down the list
    }

    // // Add the new value into that space
    // Collection<Item>::elements[i] = e;
    // Collection<Item>::curSize++;
}

// OPERATORS //
// + operator
template<typename Item>
SortedCollection<Item> &SortedCollection<Item>::operator+(Item e) {
    this -> add(e);
    return *this;
}

// Extraction operator
template<typename Item>
SortedCollection<Item> &SortedCollection<Item>::operator<< (Item in) {
    this -> add(in);
    return *this;
}

#endif //SORTEDCOLLECTION_H