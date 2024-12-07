#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <cassert>

template <typename T>
class MyDeque {

    T* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja

public:

    MyDeque(int s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor+

    ~MyDeque() { delete [] tab; }

    MyDeque(const MyDeque& other){

            msize = other.msize;
            assert(msize>0);

            tab = new T[msize];

            head = other.head;
            tail = other.tail;

            for( int i = head; i != tail; i = (i+1)%msize){
                tab[i] = other.tab[i];
            }
    } // copy constructor


    MyDeque(MyDeque&& other) noexcept{
    msize = other.msize;
    head = other.head;
    tail = other.tail;
    tab = other.tab;

    other.tab = nullptr;
    other.msize = 0;
    other.head = 0;
    other.tail = 0;
    }// move constructor NIEOBOWIĄZKOWE

    MyDeque& operator=(const MyDeque& other){
        if(this == other){
            return *this;
        }
        if(msize<other.msize){
            delete[] tab;
            msize = other.msize;
            tab = new T(msize);
        }
        head = other.head;
        tail = other.tail;
        for( int i = head; i != tail; i = (i+1)%msize){
            tab[i] = other.tab[i];
            }
        return *this;
    } // copy assignment operator, return *this

    MyDeque& operator=(MyDeque&& other) noexcept{
        
    if (this != &other) {
        delete[] tab;

        msize = other.msize;
        head = other.head;
        tail = other.tail;
        tab = other.tab;


        other.tab = nullptr;
        other.msize = 0;
        other.head = 0;
        other.tail = 0;
    }
    return *this;


    } // move assignment operator, return *this NIEOBOWIĄZKOWE

    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    int size() const { return (tail - head + msize) % msize; }
    int gdzietail()const{return tab[tail-1];}
    int czymJestTail()const{return tail;}
    int czymJestHead()const{return head;}
    int max_size() const { return msize-1; }
    void push_front(const T& item); // dodanie na początek O(1)+

    void push_front(T&& item){
        assert(!full());
        head = (head + msize -1) % msize;
        tab[head] = std::move(item);
    } // dodanie na początek O(1) NIEOBOWIĄZKOWE+

    void push_back(const T& item); // dodanie na koniec O(1)+

    void push_back(T&& item){
        assert(!full());
        tab[tail] = std::move(item);
        tail = (tail + 1) % msize;
    }
     // dodanie na koniec O(1) NIEOBOWIĄZKOWE

    T& front() { return tab[head]; } // zwraca poczatek+
    T& back() { return tab[(tail + msize -1) % msize]; } // zwraca koniec+

    void pop_front(){
        assert(!empty());
        //delete tab[head];
        //tab[head] = nullptr;
        head = (head+1)%msize;
    } // usuwa początek kolejki O(1)
    void pop_back(){
        assert(!empty());
        //delete tab[(tail + msize - 1) % msize];
        //tab[(tail + msize - 1) % msize] = nullptr;
        tail = (tail + msize-1)%msize;

    } // usuwa koniec kolejki O(1)+
    void clear(){
        assert(!empty());
        for(int i = head; i != tail; i = (i+1)%msize){
            //delete tab[i];
            //tab[i] = nullptr;
            pop_front();
        }
        delete[] tab;
        tab = nullptr;
        head = 0;
        tail = 0;
        msize = 0;
    } // czyszczenie listy z elementów !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    void display();//+

    // Operacje z indeksami. NIEOBOWIĄZKOWE+
    T& operator[](int pos){
        assert(!empty());
        assert(pos >=0);
        int index = (head+pos)%msize;
        return tab[index];
    } // podstawienie L[pos]=item, odczyt L[pos]+
    const T& operator[](int pos) const{
        assert(!empty());
        assert(pos >= 0);
        int index = (head+pos)%msize;
        return tab[index];
    } // dostęp do obiektu const+

    void erase(int pos){
        assert(!empty());
        assert (pos >= 0 && pos < tail);
        int index = (head + pos) % msize;

    if (index == head)
    {
        head = (head+1)%msize;
    }
    else if (index == (tail + msize - 1) % msize)
    {
        tail = (tail + msize-1)%msize;
    }        
    else{
        for(int i = (pos + head)%msize; i != tail-1; i=(i+1)%msize){
            tab[i] = tab[i+1];
        }
    }
        tail = (tail -1 + msize)%msize;
        //delete tab[tail];
        //tab[tail] = nullptr;
    }   
        
    int index(const T& item){
         
        for(int i = head; i != tail; i = (i+1)%msize){
            if(tab[i] == item){
                return i;
            }
        }
        return -1;
    } // jaki index na liście (-1 gdy nie ma)

    void insert(int pos, const T& item);
        
     // inserts item before pos+
    void insert(int pos, T&& item); // inserts item before pos
};
#endif

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    head = (head + msize -1) % msize;
    tab[head] = item;
}
template <typename T>
void MyDeque<T>::push_back(const T& item) {
    tab[tail] = item;
    tail = (tail + 1) % msize;
}
template <typename T>
void MyDeque<T>::display() {
    for (int i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}
template <typename T>
void MyDeque<T>::insert(int pos, const T& item) {
    assert(pos >= 0 && pos <= size());
    if (full()) {
        std::cout << "error, deque is full" << std::endl;
        return;
    }

    int index = (head + pos) % msize;
    if (pos == 0) {
        push_front(item);
    } else if (pos == size()) {
        push_back(item);
    } else {
        for (int i = tail; i != index; i = (i - 1 + msize) % msize) {
            tab[i] = tab[(i - 1 + msize) % msize];
        }
        tab[index] = item;
        tail = (tail + 1) % msize;
    }
}

template <typename T>
void MyDeque<T>::insert(int pos, T&& item) {
    assert(pos >= 0 && pos <= size());
    if (full()) {
        std::cout << "error, deque is full" << std::endl;
        return;
    }

    int index = (head + pos) % msize;
    if (pos == 0) {
        push_front(std::move(item));
    } else if (pos == size()) {
        push_back(std::move(item));
    } else {
        for (int i = tail; i != index; i = (i - 1 + msize) % msize) {
            tab[i] = tab[(i - 1 + msize) % msize];
        }
        tab[index] = std::move(item);
        tail = (tail + 1) % msize;
    }
}
