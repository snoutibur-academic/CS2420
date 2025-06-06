#pragma once
#include <cmath>
#include <iostream>
#include <memory>

using namespace std;

template<class Type>
struct Bucket {
    Type data;
    bool empty = true;
};


template<class Type>
class Hashtable;

template<class Type>
ostream &operator<<(ostream &, Hashtable<Type> &);


template<class Type>
class Hashtable {
public:
    Hashtable();

    Hashtable(int);

    Hashtable(const Hashtable<Type> &other);

    Hashtable &operator=(const Hashtable<Type> &other);

    int getSize() const;

    int getCapacity() const;

    bool empty() const;

    void insert(const Type);

    void remove(int);

    bool contains(int) const;

    void clear();

    friend ostream &operator<<<>(ostream &, Hashtable<Type> &);

private:
    int hash(int v) const;

    int capacity;
    int size;
    unique_ptr<Bucket<Type>[]> htable;
};

template<class Type>
Hashtable<Type>::Hashtable() {
    size = 0;
    capacity = 17;
    htable = make_unique<Bucket<Type>[]>(capacity);
}

template<class Type>
Hashtable<Type>::Hashtable(int capacity) : capacity(capacity) {
    size = 0;
    htable = make_unique<Bucket<Type>[]>(capacity);
}

/* operator= and copy constructor to create a deep copy of the hashtable */
template<class Type>
Hashtable<Type>::Hashtable(const Hashtable<Type> &other) {
    capacity = other.capacity;
    size = other.size;
    htable = make_unique<Bucket<Type>[]>(capacity);
    for (int i = 0; i < capacity; i++) {
        htable[i] = other.htable[i];
    }
}

template<class Type>
Hashtable<Type> &Hashtable<Type>::operator=(const Hashtable<Type> &other) {
    capacity = other.capacity;
    size = other.size;
    htable = make_unique<Bucket<Type>[]>(capacity);
    for (int i = 0; i < capacity; i++) {
        htable[i] = other.htable[i];
    }
    return *this;
}


/* Hash method to create a modulus division hash algorithm */
template<class Type>
int Hashtable<Type>::hash(int v) const {
    return ::fmod(v, capacity); // Fmod handles doubles and sends back an int.
}

template<class Type>
int Hashtable<Type>::getSize() const {
    return size;
}

template<class Type>
int Hashtable<Type>::getCapacity() const {
    return capacity;
}


template<class Type>
bool Hashtable<Type>::empty() const {
    if (size == 0) {
        return true;
    }
    return false;
}


/*
    The insert method to insert the value into the hashtable.
    Use linear probing to avoid collisions.  If the hashtable is full, return a runtime error
*/
template<class Type>
void Hashtable<Type>::insert(Type value) {
    if (size >= capacity) {
        throw runtime_error("Hashtable Full"); // Temp for now, resize later
    }

    int i = 0;
    while (!htable[hash(value + i)].empty) {
        i++;
    }

    htable[hash(value+i)] = {value, false};
    size++;
}

/* Complete the remove the value from the hashtable */
template<class Type>
void Hashtable<Type>::remove(int value) {
    int i = 0;

    while (htable[hash(value + i)].data != value && i < capacity) {
        i++;
    }

    if (i==capacity) {
        return;
    }

    htable[hash(value + i)] = {0, true};

    size--;
}

/* Complete the contains method to return true of the Hashtable contains the value */
template<class Type>
bool Hashtable<Type>::contains(int value) const {
    int i = 0;
    while (htable[hash(value + i)].data != value && i < capacity) {
        i++;
    }

    if (htable[hash(value + i)].data == value && i < capacity) {
        return true;
    }

    return false;
}


template<class Type>
void Hashtable<Type>::clear() {
    size = 0;
    htable = make_unique<Bucket<Type>[]>(capacity);
}


template<class Type>
ostream &operator<<(ostream &out, Hashtable<Type> &h) {
    out << "\nCapacity: " << h.capacity << "\n";
    for (int i = 0; i < h.capacity; i++) {
        if (h.htable[i].empty == false) {
            out << i << ": " << h.htable[i].data << endl;
        }
    }
    return out;
}
