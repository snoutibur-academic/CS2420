#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <memory>

#include "MyStack.h"

using std::ostream;
using std::shared_ptr;

template<class T>
class Queue;

template<class T>
ostream &operator<<(ostream &out, const Queue<T> &q);

template<class T>
class Queue {
public:
    Queue(); // Constructor to create an empty queue
    Queue(const Queue<T> &cpy); //  Copy constructor to create a deep copy of the queue
    Queue<T> operator=(const Queue<T> &q); // Allows the user to create a deep copy of the queue

    T peek(); //  Looks at the value at the front of the queue
    bool isEmpty(); // returns true if the queue is empty
    void enqueue(T data); // Inserts data at the back of the queue
    void dequeue(); // removes the front of the queue.
    void clear(); // empties everything out of the queue
    friend ostream &operator << <> (ostream &out, const Queue<T> &q); // returns a stream containing all the items in the Queue
private:
    shared_ptr<Node<T> > front;
    shared_ptr<Node<T> > back;
    int cnt;
};

#endif //QUEUE_HPP

// Make empty queue
template<class T>
Queue<T>::Queue() {
    front = nullptr;
    back = nullptr;
    cnt = 0;
}

// Deep copy constructor
template<class T>
Queue<T>::Queue(const Queue<T> &cpy) {
    cnt = 0;
    auto temp = cpy.front; // Start with a shallow copy
    front = make_shared<Node<T> >(temp->data); // Puts data in a new node for deep copy

    auto curr = front;
    for (int i = 0; i < cpy.cnt; i++) {
        // Add the data to queue at that point
        enqueue(temp->data);
        temp = temp->next;
    }
}

// Peek
template<class T>
T Queue<T>::peek() {
    return front->data;
}

// Emptiness check
template<class T>
bool Queue<T>::isEmpty() {
    return cnt == 0;
}

// Enqueue
template<class T>
void Queue<T>::enqueue(T data) {
    auto temp = make_shared<Node<T>>(data);

    if (cnt == 0) {
        // Empty queue, new item is front and back
        front = temp;
        back = temp;
    } else {
        back->next = temp;
        back = back->next;
    }

    cnt++;
}

// Dequeue
template<class T>
void Queue<T>::dequeue() {
    if (front == nullptr) {
        throw runtime_error("Empty queue!");
    } else {
        front = front->next;
        cnt--;
    }
}

// Clear queue
template<class T>
void Queue<T>::clear() {
    front = nullptr;
    cnt = 0;
}

// Copy operator
template<class T>
Queue<T> Queue<T>::operator=(const Queue<T> &cpy) {
    clear();

    cnt = 0;
    auto temp = cpy.front; // Start with a shallow copy
    front = make_shared<Node<T> >(temp->data); // Puts data in a new node for deep copy

    auto curr = front;
    for (int i = 0; i < cpy.cnt; i++) {
        // Add the data to queue at that point
        enqueue(temp->data);
        temp = temp->next;
    }

    return *this;
}

// Extraction op
template<class T>
ostream &operator<<(ostream &out, const Queue<T> &q) {
    auto temp = q.front;
    while (temp) {
        out << temp->data;
        if (temp->next) out << " ";
        temp = temp->next;
    }

    return out;
}
