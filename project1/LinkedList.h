# pragma once
# include <iostream>
# include <stdexcept>
# include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node* prev;
        Node* next;
    };

    LinkedList();

    ~LinkedList();

    LinkedList(const LinkedList<T> &otherList);

    void AddHead(const T& data);

    void AddTail(const T& data);

    void PrintForward();

    void PrintReverse();

    void AddNodesHead(const T* data, const int size);

    void AddNodesTail(const T* data, const int size);

    void InsertAfter(Node* x, const T& data);

    void InsertBefore(Node* x, const T& data);

    void InsertAt(const T& data, int x);

    Node* Find(const T& data);

    const Node* Find(const T& data) const;

    unsigned int NodeCount() const;

    bool RemoveHead();

    bool RemoveTail();

    int Remove(const T& data);

    bool RemoveAt(int x);

    void FindAll(vector<Node*> &list, const T& data);

    Node* GetNode(int x);

    const Node* GetNode(int x) const;

    Node* Head();

    Node* Tail();

    void Clear();

    const T &operator[](int x) const;

    T &operator[](int x);

    LinkedList<T> &operator=(const LinkedList<T>& otherList);

    bool operator==(const LinkedList<T>& otherList) const;

    void PrintForwardRecursive(const Node* x) const;

    void PrintReverseRecursive(const Node* x) const;

private:
    Node* head;
    Node* tail;
    int nodeCount = 0;
};

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &otherList) {
    Node* node = otherList.head;
    nodeCount = 0;
    head = nullptr;
    tail = nullptr;
    while(node != nullptr) {
        AddTail(node -> value);
        node = node -> next;
    }
}




template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &otherList) {
    Node* node = otherList.head;
    Node* x = head;
    Node* temp;
    if (this != &otherList) {
        nodeCount = 0;
        while ( x != nullptr) {
            temp = x -> next;
            delete x;
            x = temp;
        }
        head = nullptr;
        tail = nullptr;

        while (node != nullptr) {
            AddTail(node->value);
            node = node -> next;
        }
    }
    return *this;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &otherList) const {
    if (this->nodeCount != otherList.nodeCount) {
        return false;
    } else {
        for (int i = 0; i < otherList.nodeCount; i++) {
            if (this->GetNode(i)->value != otherList.GetNode(i)->value) {
                return false;
            }
        }
        return true;
    }
}

template<typename T>
const T &LinkedList<T>::operator[](int x) const {
    Node *start = head;
    int count = 0;
    if (LinkedList::NodeCount() < x) {
        throw std::out_of_range("Index is out of range.");
    } else {
        while (count != x) {
            start = start -> next;
            count++;
        }
        return start -> value;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}

template<typename T>
T &LinkedList<T>::operator[](int x) {
    Node *start = head;
    int count = 0;
    if (LinkedList::NodeCount() < x) {
        throw std::out_of_range("Index is out of range.");
    } else {
        while (count != x) {
            start = start -> next;
            count++;
        }
        return start -> value;
    }
}



template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node* node = new Node;
    node -> value = data;
    node -> prev = nullptr;
    node -> next = nullptr;

    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        head -> prev = node;
        node -> prev = nullptr;
        node -> next = head;
        head = node;
    }
    nodeCount++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
    Node* node = new Node;
    node -> value = data;
    node -> prev = nullptr;
    node -> next = nullptr;
    if (tail == nullptr) {
        head = node;
        tail = node;
    } else {
        tail -> next = node;
        node -> prev = tail;
        node -> next = nullptr;
        tail = node;
    }
    nodeCount++;
}

template <typename T>
void LinkedList<T>::PrintForward() {
    Node* n = head;
    while (n != nullptr) {
        cout << n -> value << endl;
        n = n -> next;
    }
}

template <typename T>
void LinkedList<T>::PrintReverse() {
    Node* n = tail;
    while (n != nullptr) {
        cout << n -> value << endl;
        n = n -> prev;
    }
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, const int size) {
    //for (int i = size; i < 0; i--) {
    for (int i = size - 1; i >= 0; i--) {
        LinkedList<T>::AddHead(data[i]);
        //nodeCount++;
    }
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, const int size) {
    for (int i = 0; i < size; i++) {
        LinkedList<T>::AddTail(data[i]);
        //nodeCount++;
    }
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* x, const T &data) {
    Node* node = new Node;
    node ->value = data;
    node ->prev = x;
    if (x == tail) {
        node ->prev = nullptr;
        tail = node;
    }
    else {
        Node* temp = x->next;
        node->next = temp;
        temp -> prev = node;
    }
    x ->next = node;
    nodeCount++;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* x, const T& data) {
    Node* node = new Node;
    node ->value = data;
    node ->next = x;

    if (x == head) {
        node ->prev = nullptr;
        head = node;
    }
    else {
        Node* temp = x->prev;
        node->prev = temp;
        temp -> next = node;
    }

    x ->prev = node;
    nodeCount++;
}

template <typename T>
void LinkedList<T>::InsertAt(const T &data, int x) {
    Node *start = head->next;
    if (x > nodeCount || nodeCount == 0) {
        throw std::out_of_range("Index is out of range.");
    } else {
        if (x == 0) {
            InsertBefore(head, data);
        } else if (x == nodeCount) {
            InsertAfter(tail, data);
        } else {
            //Node* start = head->next;
            for (int i = 1; i < x - 1; i++) {
                start = start->next;
            }
            Node* toAdd = start->next;
            Node* node = new Node;
            node->value = data;
            node->prev = start;
            node->next = toAdd;
            start->next = node;
            toAdd->prev = node;
            nodeCount++;
        }
    }
}
template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) {
    Node* node = head;
    while(node != nullptr) {
        if (node-> value == data) {
            return node;
        }
        node = node -> next;
    }
    return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) const {
    Node* node = head;
    while(node != nullptr) {
        if (node-> value == data) {
            return node;
        }
        node = node -> next;
    }
    return nullptr;
}


template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodeCount;
}
/*Node* node = head;
int count = 1;
if (head == nullptr) {
    count = 0;
}
while (node -> next != nullptr) {
    node = node -> next;
    count ++;
}
return count;
}
*/

template <typename T>
bool LinkedList<T>::RemoveHead() {
    Node* node = head;
    if (nodeCount == 0) {
        //head = nullptr;
        return false;
    } else if (nodeCount == 1) {
        delete node;
        head = nullptr;
        tail = nullptr;
        nodeCount--;
        return true;
    } else {
        Node *novel = node -> next;
        novel->prev = nullptr;
        delete head;
        head = novel;
        nodeCount--;
        return true;
    }
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
    Node* node = tail;
    if (nodeCount == 0) {
        return false;
    } else if (nodeCount == 1) {
        delete node;
        head = nullptr;
        tail = nullptr;
        nodeCount--;
        return true;
    } else {
        Node *novel = node -> prev;
        novel->next = nullptr;
        delete tail;
        tail = novel;
        nodeCount--;
        return true;
    }
}

template <typename T>
int LinkedList<T>::Remove(const T &data) {
    Node* abc;
    Node* xyz;
    int count = 0;
    vector<Node*> list;
    LinkedList<T>::FindAll(list, data);
    for (int i = 0; i < list.size(); i++) {
        count++;
        nodeCount--;
        if (list[i] == head) {
            LinkedList<T>::RemoveHead();
        } else if (list[i] == tail) {
            LinkedList<T>::RemoveTail();
        } else {
            abc = list[i] -> prev;
            xyz = list[i] -> next;
            abc -> next = xyz;
            xyz -> prev = abc;
            delete list[i];
        }
    }
    return count;
}

template <typename T>
void LinkedList<T>::FindAll(vector<LinkedList::Node *>& list, const T &data) {
    Node* node = head;
    if (node == head) {
        if (node -> value == data) {
            list.push_back(node);
            node = node -> next;
        }
    }
    while (node -> next != nullptr) {
        if (node -> value == data) {
            list.push_back(node);
            node = node -> next;
        } else {
            node = node -> next;
        }
    }
    if (node -> value == data) {
        list.push_back(node);
    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(int x) {
    Node *node = head -> next;
    int count = 1;
    if (x > nodeCount - 1 || nodeCount == 0) {
        throw std::out_of_range("Index is out of range.");
    } else {
        if (x == 0) {
            return head;
        } else {
            //Node* node = head -> next;
            for (int i = 1; i < x; i++) {
                node = node->next;
            }
            return node;
        }
    }
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(int x) const {
    Node* node = head->next;
    int count = 1;
    if (x > nodeCount - 1 || nodeCount == 0) {
        throw std::out_of_range("Index is out of range.");
    } else {
        if (x == 0) {
            return head;
        } else {
            //Node* node = head->next;
            for (int i = 1; i < x; i++) {
                node = node->next;
            }
            return node;
        }
    }
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() {
    return head;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() {
    return tail;
}

template <typename T>
bool LinkedList<T>::RemoveAt(int x) {
    Node* start = head;
    int count = 0;
    if (x > nodeCount - 1 || nodeCount == 0) {
        return false;
    } else {
        if (x == 0) {
            if (RemoveHead() == true){
                return true;
            }
        } else if (x == nodeCount - 1) {
            if (RemoveTail() == true){
                return true;
            }
        } else {
            start = GetNode(x);
            Node* abc;
            Node* xyz;
            abc = start -> prev;
            xyz = start -> next;
            abc -> next = xyz;
            xyz -> prev = abc;
            delete start;
            nodeCount--;
            return true;
        }
    }
    return false;
}

template <typename T>
void LinkedList<T>::Clear() {
    Node* node = head;
    Node* newNode;
    int count = 0;
    if (LinkedList::nodeCount == 0) {
        return;
    } else {
        while(count != LinkedList::NodeCount()) {
            newNode = node -> next;
            delete node;
            node = newNode;
            count++;
        }
    }
    nodeCount = 0;
    head = nullptr;
    tail = nullptr;
}



template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* x) const {
    if (x == nullptr)
        return;
    cout << x->value << endl;
    PrintForwardRecursive(x->next);
}

// Print Reverse Recursive
template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* x) const {
    if (x == nullptr)
        return;
    cout << x->value << endl;
    PrintReverseRecursive(x->prev);
}