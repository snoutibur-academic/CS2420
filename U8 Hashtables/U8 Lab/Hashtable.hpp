#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::make_unique;
using std::sqrt;
using std::vector;

template<class t>
struct Bucket {
    t data;
    bool empty = true;
};

template<class t>
class Hashtable {
public:
    /* Constructors */
    // Constructs and empty hash table with a default capacity of 17 and a default load factor threshold of .65
    Hashtable();

    // Constructs an empty hash table with the given capacity and a default load factor threshold of .65
    explicit Hashtable(int cap);

    // Constructs an empty hash table with the given capacity and load factor threshold values
    Hashtable(int cap, double thresh);

    // creates a deep-copy of the given hashtable
    Hashtable(const Hashtable &other);

    // replaces the current hashtable with a deep-copy of the given hash table
    Hashtable &operator=(const Hashtable &other);

    /* Getters */
    [[nodiscard]] int size() const; // returns the number of items currently in the hashtable
    [[nodiscard]] int getCapacity() const; // returns the capacity of the hashtable (i.e. the size() of the array)
    [[nodiscard]] double getLoadFactorThreshold() const; //returns the load factor threshold variable
    [[nodiscard]] bool empty() const; // returns true if the table is empty or false otherwise

    /* Find stuff */
    // Returns true if the given value is contained in the hashtable or false if the value is not in the hashtable, must use Quadratic Probing to find the element.
    [[nodiscard]] bool contains(t v);

    //Returns the index of the given value. If the value is not in the hashtable, returns -1. This is not a normal method for a hashtable and is here solely to test that your hashtable does quadratic probing.
    [[nodiscard]] int indexOf(int);

    /* Edit */
    //Inserts the given value into the hashtable.  When there are collisions, quadratic hashing is used instead of linear. Rehash() the table when the percent full reaches the loadFactorThreashold.
    void insert(int);

    // Removes the given value from the hashtable. If the value is not present it takes no action and throws no errors. Must use Quadratic Probing to find the element.
    void remove(int target);

    void clear(); //Removes all values from the hashtable, resetting it to an empty state


    /* Rehashing functions */
    // Resize() the table using the following algorithm....  double the capacity of the list and then finds the next prime number to determine the  size() of the new capacity.

    // Rehash all the items according to the new hash algorithm.  You may need to create a temporary array in order to accomplish this.  Keep in mind with unique pointers, you must use the keyword "move" to transfer ownership of the pointer.
    void rehash();

    // Takes an int parameter and returns true if the number is prime.  Used in finding the next prime number.  Note: should be static for testing purposes.  To make it static, put the word static in front of the function definition in the class.  It is not added to the function implementation after the class.
    static bool isPrime(int num);

    // Takes an int value and returns the next prime number.  Note: should also be static for testing purposes
    static int nextPrime(int num);

private:
    int filled;
    int capacity;
    double threshold;
    unique_ptr<Bucket<t>[]> htable;

    int hash(int v);
};

#endif //HASHTABLE_HPP

/* Constructors */
// Constructs and empty hash table with a default capacity of 17 and a default load factor threshold of .65
template<class t>
Hashtable<t>::Hashtable() {
    filled = 0;
    capacity = 17;
    threshold = .65;
    htable = make_unique<Bucket<t>[]>(capacity);
}

//Constructs an empty hash table with the given capacity and a default load factor threshold of .65
template<class t>
Hashtable<t>::Hashtable(int cap) {
    filled = 0;
    capacity = cap;
    threshold = .65;
    htable = make_unique<Bucket<t>[]>(capacity);
}

// Constructs an empty hash table with the given capacity and load factor threshold values
template<class t>
Hashtable<t>::Hashtable(int cap, double thresh) {
    filled = 0;
    capacity = cap;
    threshold = thresh;
    htable = make_unique<Bucket<t>[]>(capacity);
}

template<class t>
Hashtable<t>::Hashtable(const Hashtable &other) {
    capacity = other.capacity;
    filled = other.size();
    threshold = other.getLoadFactorThreshold();

    htable = make_unique<Bucket<t>[]>(capacity);
    for (int i = 0; i < capacity; i++) {
        htable[i] = other.htable[i];
    }
}

template<class t>
Hashtable<t> &Hashtable<t>::operator=(const Hashtable &other) {
    capacity = other.capacity;
    filled = other.size();
    htable = make_unique<Bucket<t>[]>(capacity);
    for (int i = 0; i < capacity; i++) {
        htable[i] = other.htable[i];
    }
    return *this;
}


/* Getters */
template<class t>
int Hashtable<t>::size() const {
    return filled;
}

template<class t>
int Hashtable<t>::getCapacity() const {
    return capacity;
}

template<class t>
double Hashtable<t>::getLoadFactorThreshold() const {
    return threshold;
}

template<class t>
bool Hashtable<t>::empty() const {
    if (filled == 0) {
        return true;
    }
    return false;
}


/* Primezz!! */
template<class t>
bool Hashtable<t>::isPrime(int num) {
    // Negative numbers can't be prime
    if (num <= 1) {
        return true;
    }

    // 2 is prime
    if (num == 2) {
        return true;
    }

    // Evens aren't primes
    if (num % 2 == 0) {
        return false;
    }

    // Other conditions
    int limit = sqrt(num);
    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

template<class t>
int Hashtable<t>::nextPrime(int num) {
    num++;
    while (!isPrime(num)) {
        num++;
    }
    return num;
}

// Generates hash for item
template<class t>
int Hashtable<t>::hash(int v) {
    // Gets the key from mod div
    int key = fmod(v, capacity);

    return key;
}

/* Find stuff */

// Returns true if the given value is contained in the hashtable or false if the value is not in the hashtable, must use Quadratic Probing to find the element.
template<class t>
bool Hashtable<t>::contains(t v) {
   // Counting collisions
    int i = 0;

    while (i < capacity) {
        if (!htable[hash(v + pow(i, 2))].empty) {
            int key = hash(v + pow(i, 2));
            if (htable[key].data == v) {
                return true;
            }
            i++;
        } else {
            i++;
        }
    }

    return false;
}

template<class t>
int Hashtable<t>::indexOf(int v) {
    // Counting collisions
    int i = 0;

    while (i < capacity) {
        if (!htable[hash(v + pow(i, 2))].empty) {
            int key = hash(v + pow(i, 2));
            if (htable[key].data == v) {
                return key;
            }
            i++;
        } else {
            i++;
        }
    }

    return -1;
}

/* Edit */
// Resize the table using the following algorithm.
template<class t>
void Hashtable<t>::rehash() {
    // Temporary to store all the data from the buckets
    vector<t> temp;
    
    for (int i = 0; i < capacity; i++) {
        // empty check
        if (!htable[i].empty) {
            temp.push_back(htable[i].data);
        }
    }
    // double the capacity of the list and then finds the next prime number to determine the size() of the new capacity
    capacity = nextPrime(capacity * 2);
    clear();
    
    // Rehash all the items according to the new hash algorithm. Keep in mind with unique pointers, you must use the keyword "move" to transfer ownership of the pointer.
    for (int i = 0; i < temp.size(); i++) {
        insert(temp[i]);
    }
}

//Inserts the given value into the hashtable.
//When there are collisions, quadratic hashing is used instead of linear.
//Rehash() the table when the percent full reaches the loadFactorThreashold.
template<class t>
void Hashtable<t>::insert(const int toAdd) {
    // No overfilling
    if (double(filled + 1) / double(capacity) >= threshold) {
        rehash();
    }

    // Checks availability
    int i = 0;

    while (i < capacity) {
        if (!htable[hash(toAdd + pow(i, 2))].empty) {
            // Collision found
            i++;
        } else {
            // Insert at available spot as there's no collision
            int key = hash(toAdd + pow(i, 2));
            htable[key] = {toAdd, false};
            filled++;
            break;
        }
    }
}

// Removes the given value from the hashtable. If the value is not present it takes no action and throws no errors. Must use Quadratic Probing to find the element.
template<class t>
void Hashtable<t>::remove(int v) {
    // Counting collisions
    int i = 0;

    while (i < capacity) {
        if (!htable[hash(v + pow(i, 2))].empty) {
            int key = hash(v + pow(i, 2));
            if (htable[key].data == v) {
                htable[key] = {0, true};
                filled--;
                return;
            }
            i++;
        } else {
            i++;
        }
    }
}

template<class t>
void Hashtable<t>::clear() {
    filled = 0;
    htable = make_unique<Bucket<t>[]>(capacity);
}
