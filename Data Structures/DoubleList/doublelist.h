// doublelist.h
#include <iostream>
#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
    int rozmiar = 0;
public:
    DoubleList() : head(nullptr), tail(nullptr), rozmiar(0) {}
    ~DoubleList(){
        
        
        //DoubleNode<T> *node_prv = tail; 
        DoubleNode<T> *node_nxt = head; 
        rozmiar = 0;
        
        while(!empty()){

            //node_prv = tail->prev;
            node_nxt = head->next;
            //delete tail;
            delete head;
            head = node_nxt;
            //tail = node_prv;
        }
    }// tu trzeba wyczyscic wezly+

    DoubleList(const DoubleList& other){

        //DoubleNode<T> *current_prv = other.tail; 
        head = nullptr;
        tail = nullptr;
        DoubleNode<T> *current_nxt = other.head; 
        rozmiar = 0;

        while(current_nxt){

            //push_front(current_nxt->value);
            push_back(current_nxt->value);

            //current_prv = current_prv->prev;
            current_nxt = current_nxt->next;
        }
    }     // copy constructor
    // usage:   DoubleList<int> list2(list1);+

    DoubleList(DoubleList&& other){
        
    head = other.head;
    tail = other.tail;
    rozmiar = other.rozmiar;

    other.head = nullptr;
    other.tail = nullptr;
    other.rozmiar = 0;

    } // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));+

    DoubleList& operator=(const DoubleList& other){
    if (this == &other) {
        return *this;
    }
    
    rozmiar = 0;
    clear();
    DoubleNode<T> *current = other.head;

    while(head != other.tail) {
        push_back(current->value);
        head = current->next;
    }
    return *this;
    }
    // copy assignment operator, return *this
    // usage:   list2 = list1;+

    DoubleList& operator=(DoubleList&& other)
    {
        if (this == &other) {
        return *this;
    }

        clear();

        DoubleNode<T> *current = other.head;
        rozmiar = other.rozmiar;
        DoubleNode<T> *temp = current;
        temp->next = current->next;
        temp->prev = nullptr;
        while(current){
            head = current;
            current = current->next;
            current->prev = head;
        }

        tail = current;
        tail->next = nullptr;
        tail->prev = current->prev;
        head = temp;

        delete current;
        delete temp;

        other.clear();
        other.rozmiar = 0;

    return *this;
    }// move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE+

    bool empty() const { return head == nullptr; }
    int size() const{return rozmiar;} // O(n) bo trzeba policzyc+

    void push_front(T&& item) {
    if (!empty()) {
        DoubleNode<T> *newHead = new DoubleNode<T>(std::move(item), head);
        newHead->next = head;
        head->prev = newHead;
        head = newHead;
        head->prev= nullptr;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
    rozmiar++;
    } // O(1) NIEOBOWIAZKOWE+

    void push_front(const T& item) {
        if (!empty()) {
            DoubleNode<T> *newHead = new DoubleNode<T>(item, head);
            newHead->next = head;
            head->prev = newHead;
            head = newHead;
            head->prev = nullptr;
        } else {
            head = tail = new DoubleNode<T>(item);
        }
        rozmiar++;
    }


    void push_back(const T& item){
        if (!empty()) {

            DoubleNode<T> *newTail = new DoubleNode<T>(item, tail);
            newTail->prev = tail;
            tail->next = newTail;
            tail = newTail;
        } 
        else {
           head = tail = new DoubleNode<T>(item, nullptr, nullptr);
        }
        rozmiar++;
    } // O(1)

    void push_back(T&& item){

        if (!empty()) {
            DoubleNode<T> *newTail = new DoubleNode<T>(std::move(item));
            newTail->prev = tail;
            tail->next = newTail;
            tail = newTail;
         
        }
        else {
            head = tail = new DoubleNode<T>(std::move(item), nullptr, nullptr);
        }
        rozmiar++;
    } // O(1) NIEOBOWIAZKOWE

    T& front() const { return head->value; } // zwraca poczatek, nie usuwa+
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa+

    void pop_front(){
        assert(!empty());
        DoubleNode<T> *node = head;
        if(head == tail){
            head = tail = nullptr;

        }
        else{
            
            rozmiar--;
            head = head->next;
            head->prev = nullptr;
            delete node;
        }
        
        
    } // usuwa poczatek O(1)+
    void pop_back(){
        assert(!empty());

        if(head == tail){
            delete tail;
            head = tail = nullptr; 
        }
        else{ 
            DoubleNode<T>*  temp = tail->prev;
            //tail = tail->prev;
            //tail->next = nullptr;
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        rozmiar--; 
    }

 // usuwa koniec O(1)+

    void clear(){
        assert(!empty());
        while(head){

            DoubleNode<T> *temp_h = head;
            //DoubleNode<T> *temp_t = tail;

            head = head->next;
            //tail = tail->prev;
            delete temp_h;
            //delete temp_t;
        }
        head = tail = nullptr;
        rozmiar = 0;
    } // czyszczenie listy z elementow O(n)+

    void display(){
        DoubleNode<T> *node = head;
        while (node != nullptr){
            std::cout << node->value << " ";
            node = node->next;
        }
        std::cout << std::endl;
    } // O(n)+

    void display_reversed(){

        DoubleNode<T> *node = tail;
        DoubleNode<T> *node1 = head->prev;
        std::cout << (node1 == nullptr) << std::endl;
        //head->prev = nullptr;
        while (node != head->prev){
            std::cout << node->value << " ";
            node = node->prev;
        }
        std::cout << std::endl;
    } // O(n)+

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](int pos){
        assert(pos >=0);
        DoubleNode<T> *node = nullptr;
        if(rozmiar/2 <= pos){
            node = tail;
            for(int i = rozmiar; i > pos; i--){
                node = node->prev;
            }
        }
        else{
            node = head;
            for( int i = 0; i < pos; i++){
                node = node->next;
            }
        }
        return node->value;
    } // podstawienie L[pos]=item, odczyt L[pos]+

    const T& operator[](int pos) const{
        assert(pos >=0);
        DoubleNode<T> *node = nullptr;
        if(rozmiar/2 <= pos){
            node = tail;
            for(int i = rozmiar; i > pos; i--){
                node = node->prev;
            }
        }
        else{
            node = head;
            for( int i = 0; i < pos; i++){
                node = node->next;
            }
        }
        return node->value;
    } // dostep do obiektu const+
    void erase(int pos){
        if (pos < 0 || pos >= size()) {
        return;
    }

    if (pos == 0) {
        DoubleNode<T> *temp = head;
        head = head->next;
        delete temp;
    } else {
        DoubleNode<T> *previous = head;
        for (int i = 0; i < pos - 1; i++) {
            previous = previous->next;
        }

        DoubleNode<T> *temp = previous->next;
        previous->next = temp->next;
        delete temp;
    }

    rozmiar--;
    }

    int index(const T& item){
    DoubleNode<T> *current = head;
    int currentIndex = 0;

    while (current) {
        if (current->value == item) {
            return currentIndex; 
        }
        current = current->next;
        currentIndex++;
    }

    return -1;
    } // jaki index na liscie (-1 gdy nie ma) O(n)+

    void insert(int pos, const T& item){
        if (pos < 0) {
        push_front(item);
        } 
        else if (pos == size()) {
        push_back(item);
        } 
        else {

        DoubleNode<T> *current = head;
        DoubleNode<T> *previous = nullptr;
        for (int i = 0; i < pos; i++) {
            previous = current;
            current = current->next;
        }

        DoubleNode<T> *newNode = new DoubleNode<T>(item, current, previous);
        if (previous) {
            previous->next = newNode;
            current->prev = newNode;
        } 
        else {
            head = newNode;
        }
        rozmiar++;
    }
    } // inserts item before pos,+

    void insert(int pos, T&& item){
        if (pos < 0) {

        push_front(std::move(item));
    } else if (pos == size()) {

        push_back(std::move(item));
    } else {
        DoubleNode<T> *current = head;
        DoubleNode<T> *previous = nullptr;
        for (int i = 0; i < pos; i++) {
            previous = current;
            current = current->next;
        }
        DoubleNode<T> *newNode = new DoubleNode<T>(std::move(item), current, previous);
        if (previous) {
            previous->next = newNode;
            current->prev = newNode;
        } else {
            head = newNode;
        }
        rozmiar++;
    }
    } // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};



#endif

// EOF
