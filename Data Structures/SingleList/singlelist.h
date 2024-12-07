// singlelist.h

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct SingleNode {
// the default access mode and default inheritance mode are public
    T value;
    SingleNode *next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T& item, SingleNode *ptr=nullptr) : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T>
class SingleList {
    SingleNode<T> *head, *tail;
    int rozmiar;
public:
    SingleList() : head(nullptr), tail(nullptr), rozmiar(0) {}
    ~SingleList(); // tu trzeba wyczyscic wezly+

    SingleList(const SingleList& other); // copy constructor+
    // usage:   SingleList<int> list2(list1);

    SingleList(SingleList&& other); // move constructor NIEOBOWIAZKOWE+
    // usage:   SingleList<int> list2(std::move(list1));

    SingleList& operator=(const SingleList& other){
    if (this == &other) {
        return *this;
    }
    
    this->rozmiar = 0;
    clear();
    SingleNode<T> *current = other.head;
    while (current) {
        push_back(current->value);
        this->rozmiar++;
        current = current->next; 
    }
    return *this;
    } // copy assignment operator, return *this+
    // usage:   list2 = list1;

    SingleList& operator=(SingleList&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();

    head = other.head;
    tail = other.tail;
    rozmiar = other.rozmiar;

    other.head = nullptr;
    other.tail = nullptr;
    other.rozmiar = 0;

    return *this;
} // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE+

    bool empty() const { return head == nullptr; }
    int size() const{return rozmiar;} // O(n) bo trzeba policzyc+
    void push_front(const T& item); // O(1), L.push_front(item)+
    void push_front(T&& item); // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1), L.push_back(item)+
    void push_back(T&& item); // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa+
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa+
    void pop_front(); // usuwa poczatek O(1)+
    void pop_back(); // usuwa koniec O(n)+
    void clear(); // czyszczenie listy z elementow O(n)+
    void display(); // O(n)+
    void reverse(); // O(n)+

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](int pos); // podstawienie L[pos]=item, odczyt L[pos]+
    const T& operator[](int pos) const; // dostep do obiektu const+
    void erase(int pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T& item); // inserts item before pos,
    void insert(int pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
SingleList<T>::~SingleList() {
    // I sposob.
    for (SingleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    // II sposob.
    // while (!empty()) { pop_front(); }
}

template <typename T>
SingleList<T>::SingleList(const SingleList<T>& other){
    
    rozmiar = 0;

    SingleNode<T> *current = other.head;
    while (current)
    {
        push_back(current->value);  
        current = current->next;
        rozmiar++; 
    }
}
template <typename T>
SingleList<T>::SingleList(SingleList<T> &&other)
{
    head = other.head;
    tail = other.tail;
    rozmiar = other.rozmiar;

    other.head = nullptr;
    other.tail = nullptr;
    other.rozmiar = 0;
}


/*SingleList& operator=(const SingleList& other){
    if (this == &other) {
        return *this;
    }
    
    this->rozmiar = 0;
    clear();
    SingleNode<T> *current = other.head;
    while (current) {
        push_back(current->value);
        this->rozmiar++;
        current = current->next; 
    }
    return *this;
}
*/
/*SingleList& operator=(SingleList&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();

    head = other.head;
    tail = other.tail;
    rozmiar = other.rozmiar;

    other.head = nullptr;
    other.tail = nullptr;
    other.rozmiar = 0;

    return *this;
}
*/
template <typename T>
void SingleList<T>::push_front(const T &item)
{
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    } else {
        head = tail = new SingleNode<T>(item);
    }
    rozmiar++;
}

template <typename T>
void SingleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new SingleNode<T>(std::forward<T>(item), head);
    } else {
        head = tail = new SingleNode<T>(std::forward<T>(item));
    }
    rozmiar++;
}

template <typename T>
void SingleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(item);
    }
    rozmiar++;
}

template <typename T>
void SingleList<T>::push_back(T&& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(std::forward<T>(item));
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(std::forward<T>(item));
    }
    rozmiar++;
}

template <typename T>
void SingleList<T>::display() {
    SingleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SingleList<T>::pop_front() {
    assert(!empty());
    SingleNode<T> *node = head; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        head = head->next;
        rozmiar--;
    }
    delete node;
}

template <typename T>
void SingleList<T>::pop_back() {
    assert(!empty());
    SingleNode<T> *node = tail; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        // Szukamy poprzednika ogona.
        SingleNode<T> *before=head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
        rozmiar--;
    }
    delete node;
}
template <typename T> 
    void SingleList<T>::reverse(){
        assert(!empty());
        SingleNode<T> *current = head;
        SingleNode<T> *previous = nullptr;

        while (current) {
            SingleNode<T> *next = current->next;
            current->next = previous;
            previous = current;
            current = next;
    }
        SingleNode<T> *temp = head;
        head = tail;
        tail = temp;
}

template <typename T> 
void SingleList<T>::clear(){
        assert(!empty());
        while(head){
            SingleNode<T> *temp = head;
            head = head->next;
            delete temp;
        }
        rozmiar = 0;
        
        }
template <typename T>         
T& SingleList<T>::operator[](int pos){
    assert(pos >= 0);
    SingleNode<T> *current = head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    return current->value;
}

template <typename T> 
const T& SingleList<T>::operator[](int pos) const{

    assert(pos >= 0); 
    SingleNode<T> *current = head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    return current->value;
}
template <typename T>  
void SingleList<T>::erase(int pos) {
    if (pos < 0 || pos >= size()) {
        return;
    }

    if (pos == 0) {
        SingleNode<T> *temp = head;
        head = head->next;
        delete temp;
    } else {
        SingleNode<T> *previous = head;
        for (int i = 0; i < pos - 1; i++) {
            previous = previous->next;
        }

        SingleNode<T> *temp = previous->next;
        previous->next = temp->next;
        delete temp;
    }

    rozmiar--;
}
template <typename T>  
int SingleList<T>::index(const T& item) {
    SingleNode<T> *current = head;
    int currentIndex = 0;

    while (current) {
        if (current->value == item) {
            return currentIndex; 
        }
        current = current->next;
        currentIndex++;
    }

    return -1;
}
template <typename T>  
void SingleList<T>::insert(int pos, const T& item) {
    if (pos < 0) {
        push_front(item);
    } else if (pos == size()) {
        push_back(item);
    } else {
        // Вставляем перед указанной позицией
        SingleNode<T> *current = head;
        SingleNode<T> *previous = nullptr;
        for (int i = 0; i < pos; i++) {
            previous = current;
            current = current->next;
        }
        SingleNode<T> *newNode = new SingleNode<T>(item, current);
        if (previous) {
            previous->next = newNode;
        } else {
            head = newNode;
        }
        rozmiar++;
    }
}
template <typename T>  
void SingleList<T>::insert(int pos, T&& item) {
    if (pos < 0) {

        push_front(std::move(item));
    } else if (pos == size()) {

        push_back(std::move(item));
    } else {
        // Вставляем перед указанной позицией
        SingleNode<T> *current = head;
        SingleNode<T> *previous = nullptr;
        for (int i = 0; i < pos; i++) {
            previous = current;
            current = current->next;
        }
        SingleNode<T> *newNode = new SingleNode<T>(std::move(item), current);
        if (previous) {
            previous->next = newNode;
        } else {
            head = newNode;
        }
        rozmiar++;
    }
}


#endif