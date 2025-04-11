//
// Created by doge on 2/5/25.
//

#ifndef FIFTHELEMENT_H
#define FIFTHELEMENT_H
#include "LinkedList.h"

template<class T>
class FifthElement : public LinkedList<T> {
public:
    // This method returns the data at the fifth node (not index) of the linked list. It will throw a runtime_error. (just like in peek()) if there is no fifth element in the list
    T getFifthElement();

    // This method inserts a node containing value between the existing 4 and 5 nodes so that the original 5th node becomes the 6 node in the list. If there are only 4 nodes in the list, the new node will become the last node in the list.
    void insertNewFifthElement(const T&value);

    // This method deletes the 5th node. If there was a 6th node, the 4th node now points to the 6th node. If there was no 6th node, the 4th node becomes the new back node.
    void deleteFifthElement();

    // This method rearranges the 4th and 5th nodes. It cannot swap the data in the nodes, it instead must rearrange pointers.
    void swapFourthAndFifthElement();
};

#endif //FIFTHELEMENT_H


template<class T>
T FifthElement<T>::getFifthElement() {
    // Catch out of bounds
    if (4 >= this->count) {
        throw runtime_error("Out of range");
    }

    // Find and return 5th
    int currNodeNum = 0;
    auto currentNode = this->front;

    while (currNodeNum < 4) {
        currNodeNum++;
        currentNode = currentNode->next;
    }

    return currentNode->data;
}

template<class T>
void FifthElement<T>::insertNewFifthElement(const T &data) {
    // Less than 5
    if (this->count < 5) {
        LinkedList<T>::insert(data);
        return;
    }

    // Make the new node
    auto temp = make_shared<Node<T>>(); // Doing a type of Note<Type>.
    temp->data = data;
    temp->next = nullptr;

    // loop that goes to 4th element
    auto currentNode = this->front;
    // Moving the pointer / cursor to the 5th
    for (int i = 0; i < 3; i++) { // Goes to third for accessing the 4th and next elements
        currentNode = currentNode->next;
    }

    // link new 5th to 6th next
    temp->next = currentNode->next;

    // link 4th to 5th
    currentNode->next = temp;

    this->count++;
}

template<class T>
void FifthElement<T>::deleteFifthElement() {
    // loop that goes to 4th element
    auto currentNode = this->front;
    for (int i = 0; i < 3; i++) {
        currentNode = currentNode->next;
    }

    // link 4th to 6th
    currentNode->next = currentNode->next->next;
    // 5th element is auto deleted because it's using smart pointers

    this->count--;
    if (!currentNode->next) {
        this->back = currentNode;
    }
}

template<class T>
void FifthElement<T>::swapFourthAndFifthElement() {
    auto third = this->front;
    for (int i = 0; i < 2; i++) {
        third = third->next;
    }
    auto fourth = third->next;
    auto fifth = fourth->next;
    auto sixth = fifth->next;

    // Link 3 & 5
    third->next = fifth;

    // Link 5 & 4
    fifth->next = fourth;

    // Link 4 & 6
    fourth->next = sixth;

    if (this->count == 5) {
        this->back = fourth;
    }
}