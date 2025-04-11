#include <iostream>
#include <memory>
using namespace std;

template<typename T>
struct Node {
    Node(T data): data(data), left(nullptr), right(nullptr) {
    };
    T data;
    shared_ptr<Node<T> > left;
    shared_ptr<Node<T> > right;
};

template<typename T>
class BTree {
public:
    // Constructors //
    BTree(): root(nullptr) {
    };
ee<T> &);

    BTree<T> &operator=(const BTree<T> &);

    // Edit //
    void insert(const T &item);

    //The remove will remove the given node from the list.  Remember there are four situations, no children, left child right child, and two children. 
    void remove(const T &item);

    void remove(const T &item, shared_ptr<Node<T> > ptr);

    // Display //
    void preOrder();

    void inOrder();

    void postOrder();

    // Counters //
    int nodeCount();

    int leavesCount();

    // Findy thingies //
    //The find method will be given a value and it will return the node that contains that particular value You might need an extra method to help with the recursion on this one much like the traversals
    shared_ptr<Node<T> > find(const T &item);

    shared_ptr<Node<T> > find(const T &item, shared_ptr<Node<T> > ptr);


    //findRightMostNode() is a helper method used in the remove() function.  It should normally be a private method, but leave it public for testing purposes. Given a tree and a node, it will find the right most node of the branch from the given node
    shared_ptr<Node<T> > findRightMostNode();

    shared_ptr<Node<T> > findRightMostNode(shared_ptr<Node<T> > ptr);

    //findParent() is a helper method used in the remove() function. It should normally be a private method, but leave it public for testing purposes. Given a tree and a node, it will find the right the parent of the given node.
    shared_ptr<Node<T> > findParent(shared_ptr<Node<T> > ptr);

private:
    void insert(const T &item, shared_ptr<Node<T> > ptr);

    void preOrder(shared_ptr<Node<T> > ptr);

    void inOrder(shared_ptr<Node<T> > ptr);

    void postOrder(shared_ptr<Node<T> > ptr);

    int nodeCount(shared_ptr<Node<T> > ptr);

    int leavesCount(shared_ptr<Node<T> > ptr);

    shared_ptr<Node<T> > copyNode(shared_ptr<Node<T> > ptr);

    shared_ptr<Node<T> > root;
};

// CONSTRUCTORS //
template<typename T>
BTree<T>::BTree(const BTree<T> &b) {
    root = copyNode(b.root);
}

template<typename T>
BTree<T> &BTree<T>::operator=(const BTree<T> &) {
    return BTree(*this); // shortcut to use the copy constructor and return it!!
}

template<typename T>
shared_ptr<Node<T> > BTree<T>::copyNode(shared_ptr<Node<T> > ptr) {
    if (ptr == nullptr) {
        return nullptr;
    }

    auto ptrCopy = make_shared<Node<T> >(ptr->data);
    ptrCopy->left = copyNode(ptr->left);
    ptrCopy->right = copyNode(ptr->right);
    return ptrCopy;
}


// EDIT //
// Insert
template<typename T>
void BTree<T>::insert(const T &item) {
    if (root == nullptr) {
        root = make_shared<Node<T> >(item);
    } else {
        insert(item, root);
    }
}

template<typename T>
void BTree<T>::insert(const T &item, shared_ptr<Node<T> > ptr) {
    if (item < ptr->data) {
        // Left branch
        if (ptr->left == nullptr) {
            ptr->left = make_shared<Node<T> >(item);
        } else {
            insert(item, ptr->left);
        }
    } else {
        // right branch
        if (ptr->right == nullptr) {
            ptr->right = make_shared<Node<T> >(item);
        } else {
            insert(item, ptr->right);
        }
    }
}

// Remove
template<typename T>
void BTree<T>::remove(const T &item) {
    remove(item, root);
}

template<typename T>
void BTree<T>::remove(const T &item, shared_ptr<Node<T> > ptr) {
    // Nothing to delete
    if (ptr == nullptr) {
        return;
    }

    // Locate node
    if (item > ptr->data) {
        return remove(item, ptr->right);
    }
    if (item < ptr->data) {
        return remove(item, ptr->right);
    }

    // Item found!
    if (ptr->left == nullptr) {
        // Reroute parent to right branch
    } else if (ptr->right == nullptr) {
        // reroute parent to the left branch
    } else {
        /* This means this node has multiple children. Rerouting this will make it so that an entire branch gets deleted. */
    }
}


// COUNTERS //
template<typename T>
int BTree<T>::nodeCount() {
    return nodeCount(root);
}

template<typename T>
int BTree<T>::nodeCount(shared_ptr<Node<T> > ptr) {
    if (ptr) {
        return 1 + nodeCount(ptr->left) + nodeCount(ptr->right);
    }

    return 0;
}


template<typename T>
int BTree<T>::leavesCount() {
    return leavesCount(root);
}

template<typename T>
int BTree<T>::leavesCount(shared_ptr<Node<T> > ptr) {
    if (!ptr) {
        return 0;
    }

    if (ptr->right == nullptr && ptr->left == nullptr) {
        // If left and right are null, count it as 1
        return 1;
    }

    return leavesCount(ptr->left) + leavesCount(ptr->right);
}


// DISPLAY //
template<typename T>
void BTree<T>::preOrder() {
    // starts recursion
    preOrder(root);
}

template<typename T>
void BTree<T>::preOrder(shared_ptr<Node<T> > ptr) {
    if (ptr) {
        cout << ptr->data << " ";
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}


template<typename T>
void BTree<T>::inOrder() {
    inOrder(root);
}

template<typename T>
void BTree<T>::inOrder(shared_ptr<Node<T> > ptr) {
    if (ptr) {
        preOrder(ptr->left);
        cout << ptr->data << " ";
        preOrder(ptr->right);
    }
}


template<typename T>
void BTree<T>::postOrder() {
    postOrder(root);
}

template<typename T>
void BTree<T>::postOrder(shared_ptr<Node<T> > ptr) {
    if (ptr) {
        preOrder(ptr->left);
        preOrder(ptr->right);
        cout << ptr->data << " ";
    }
}

// Findy Thingies
template<typename T>
shared_ptr<Node<T> > BTree<T>::find(const T &item) {
    return find(item, root);
}

template<typename T>
shared_ptr<Node<T> > BTree<T>::find(const T &item, shared_ptr<Node<T> > ptr) {
    if (item < ptr->data) {
        // Traversing left branch
        if (ptr->left->data == item) {
            return ptr->left;
        } else {
            find(item, ptr->left);
        }
    } else {
        // Traverse the right branch
        if (ptr->right->data == item) {
            return ptr->right;
        } else {
            find(item, ptr->right);
        }
    }
}

template<typename T>
shared_ptr<Node<T> > BTree<T>::findRightMostNode() {
    findRightMostNode(root);
}

template<typename T>
shared_ptr<Node<T> > BTree<T>::findRightMostNode(shared_ptr<Node<T> > ptr) {
    if (ptr->right == nullptr) {
        return ptr;
    } else {
        return findRightMostNode(ptr->right);
    }
}

template<typename T>
shared_ptr<Node<T> > BTree<T>::findParent(shared_ptr<Node<T> > ptr) {
    // Locate specified node, go up 1 level, return that node
    return nullptr;
}
