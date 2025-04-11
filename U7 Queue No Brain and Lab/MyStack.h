#include <iostream>
#include <memory>

using std::shared_ptr;
using std::ostream;
using std::make_shared;
using std::runtime_error;

template <class Type>
struct Node {
    Node(Type data): data(data), next(nullptr) {}; // nodes can have constructors
    Type data;
    shared_ptr<Node<Type>> next;
};

template <class Type>
class MyStack;

template <class Type>
ostream &operator<< (ostream &out, const MyStack<Type> &q);

template <class Type>
class MyStack
{
public:
    MyStack();					//Constructor
    MyStack(const MyStack &);	//Copy Constructor
    //~Queue();					//Destructor if using raw pointers
    void push(Type item);		//Adds an item
    void pop();					//Removes an item
    Type peek();				//Returns the top value
    int size();					//Returns the size
    bool isEmpty();				//Returns true if empty
    void clear();				//Erases all the items
    MyStack<Type>& operator=(const MyStack<Type>& other);	//Deep copy
    friend ostream &operator<< <>(ostream &out, const MyStack<Type> &q);  //Displays all the items
private:
    shared_ptr<Node<Type>> top;
    int cnt;
};

template <class Type>
MyStack<Type>::MyStack() {
    top = nullptr;
    cnt = 0;
}

template <class Type>
MyStack<Type>::MyStack(const MyStack<Type> &other) {
    cnt = 0;
    auto temp = other.top; // this is a shallow copy of the other pointer
    top = make_shared<Node<Type>>(temp->data); // instantiate node w/ data, makes the deep copy
    cnt++;

    auto curr = top;
    for (int i=0; i < other.cnt; i++) {
        // Adding the new nodes
        auto newPtr = make_shared<Node<Type>>(temp->data);
        curr->next = newPtr;

        // Moving the cursor
        curr = curr->next;
        temp = temp->next;
        cnt++;
    }
}

/* For raw pointers
template <class Type>
Queue<Type>::~Queue() {
    clear()
}
*/

template <class Type>
void MyStack<Type>::push(Type item) {
    auto temp = make_shared<Node<Type>>(item);

    if (cnt == 0) {
        top = temp; // empty, make the top the item
    } else {
        // If it ain't empty, then relink values
        temp->next = top;
        top = temp;
    }
    cnt++;
}

template <class Type>
Type MyStack<Type>::peek() {
    if (top == nullptr) {
        // no crash on looking at empty list
        throw runtime_error("Empty stack");
    } else {
        return top->data;
    }
}
template <class Type>
int MyStack<Type>::size() {
    return cnt;
}
template <class Type>
bool MyStack<Type>::isEmpty() {
    return cnt == 0;
}
template <class Type>
void MyStack<Type>::clear() {
    // Smart pointers, it'll take care of all the nonexistent data for us.
    top = nullptr;
    cnt = 0;

    // For raw pointers
    /* auto temp = top;
    while (top) {
        top=top->next;
        delete temp;
        temp = top;
    }
    */
}

template <class Type>
void MyStack<Type>::pop() {
    if (top == nullptr) {
        throw runtime_error("Empty stack");
    } else {
        top = top-> next;
        cnt--;
    }
}

template <class Type>
MyStack<Type>& MyStack<Type>::operator=(const MyStack& other) {
    clear();

    auto temp = other.top; // this is a shallow copy of the other pointer
    top = make_shared<Node<Type>>(temp->data); // instantiate node w/ data, makes the deep copy
    cnt++;

    auto curr = top;
    for (int i=0; i < other.cnt; i++) {
        // Adding the new nodes
        auto newPtr = make_shared<Node<Type>>(temp->data);
        curr->next = newPtr;

        // Moving the cursor
        curr = curr->next;
        temp = temp->next;
        cnt++;
    }

    return *this;
}

template <class Type>
ostream& operator<<(ostream& out, const MyStack<Type> &q)
{
    auto temp = q.top;
    while (temp) {
        out << temp->data;
        if (temp->next) out << " ";
        temp = temp->next;
    }
    return out;
}