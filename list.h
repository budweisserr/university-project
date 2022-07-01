#pragma once

template <typename T>
class list {
public:
    list();
    list(const list& l);
    list& operator=(const list& l);
    ~list();

    T& operator[](int index);
    unsigned size();
    bool isEmpty() const;
    void push_front(const T& val);
    void push_back(const T& val);
    T head();
    T tail();
    void pop_front();
    void pop_back();
    void pop(int index);
    void clear();
private:
    struct Node {
        Node* next;
        Node* prev;
        T value;
    };

    Node* first; 
    Node* last;  
    unsigned length; 
    void createEmpty();
    void copyAll(const list& l);

};
template <typename T>
T& list<T>::operator[](int index) {
    Node* current = first;
    int counter = 0;
    while (current->next != nullptr) {
        if (counter == index) {
            break;
        }
        current = current->next;
        counter++;
    }
    return current->value;
}

template <typename T>
void list<T>::createEmpty() {
    first = nullptr;
    last = nullptr;
    length = 0;
}

template <typename T>
void  list<T>::clear() {
    while (!isEmpty()) {
        pop_front();
    }
}

template <typename T>
void list<T>::copyAll(const list& l) {
    Node* iterator = l.first;
    while (iterator) {
        T obj = iterator->value;
        push_back(obj);
        iterator = iterator->next;
    }
}

template <typename T>
unsigned list<T>::size() {
    return length;
}

template <typename T>
bool list<T>::isEmpty() const {
    return (first == nullptr && last == nullptr);
}

template <typename T>
void list<T>::push_front(const T& val) {
    Node* newNode = new Node;
    new (&(newNode->value)) T(val);
    newNode->next = first;
    newNode->prev = nullptr;
    if (isEmpty()) first = last = newNode;
    else {
        first->prev = newNode;
        first = newNode;
    }
    length++;
}

template <typename T>
void list<T>::push_back(const T& val) {
    Node* newNode = new Node;
    new (&(newNode->value)) T(val);
    newNode->next = nullptr;
    newNode->prev = last;
    if (isEmpty()) first = last = newNode;
    else {
        last->next = newNode;
        last = newNode;
    }
    length++;
}

template <typename T>
T list<T>::head() {
    return first->value;
}

template <typename T>
T list<T>::tail() {
    return last->value;
}

template <typename T>
void list<T>::pop_front() {
    if (isEmpty()) return;
    Node* removedNode = first;
    first = first->next;
    if (first) first->prev = nullptr;
    else first = last = nullptr;
    delete removedNode;
    length--;
    return;
}

template <typename T>
void list<T>::pop_back() {
    if (isEmpty()) return;
    Node* removedNode = last;
    last = last->prev;
    if (last) last->next = nullptr;
    else first = last = nullptr;
    delete removedNode;
    length--;
    return;
}

template <typename T>
void list<T>::pop(int index) {
    if (index + 1 == 1) pop_front();
    if (index == size() - 1) pop_back();
    if (isEmpty()) return;
    Node* removedNode = first;
    int counter = 0;
    while (removedNode != nullptr) {
        if (counter == index) {
            removedNode->prev->next = removedNode->next;
            removedNode->next->prev = removedNode->prev;
            delete removedNode;
            length--;
            return;
        }
        counter++;
        removedNode = removedNode->next;
    }
}

template <typename T>
list<T>::list() {
    createEmpty();
}

template <typename T>
list<T>::list(const list& l) {
    createEmpty();
    copyAll(l);
    return;
}

template <typename T>
list<T>& list<T>::operator= (const list& l)
{
    if (this != &l) {
        clear();
        copyAll(l);
    }
    return *this;
}

template <typename T>
list<T>::~list() {
    clear();
}

