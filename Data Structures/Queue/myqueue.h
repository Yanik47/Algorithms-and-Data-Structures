#include <iostream>
#include <cassert>
template <typename T>
class MyQueue
{
    T *tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head;  // pierwszy do pobrania
    int tail;  // pierwsza wolna pozycja
public:
    MyQueue(int s = 10) : msize(s + 1), head(0), tail(0)
    {
        tab = new T[s + 1];
        assert(tab != nullptr);
    } // default constructor
    ~MyQueue() { delete[] tab; }
    MyQueue(const MyQueue &other){
        msize = other.msize;
        assert(msize>0);
        tab = new T[msize];
        head = other.head;
        tail = other.tail;
        for( int i = head; i != tail; i = (i+1)%msize){
                tab[i] = other.tab[i];
            }
    }            // copy constructor
    MyQueue(MyQueue &&other){
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        tab = other.tab;

        other.tab = nullptr;
        other.msize = 0;
        other.head = 0;
        other.tail = 0;
    }                 // move constructor
    MyQueue &operator=(const MyQueue &other){
        if(other == this){
            return *this;
        }
        msize = other.msize;
        assert(msize>0);
        tab = new T[msize];
        head = other.head;
        tail = other.tail;
        for( int i = head; i != tail; i = (i+1)%msize){
                tab[i] = other.tab[i];
            }
        return *this;
    } // copy assignment operator, return *this

    MyQueue &operator=(MyQueue &&other){
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
    }      // move assignment operator, return *this
    bool empty() const { return head == tail; }
    bool full() const { return (head + msize - 1) % msize == tail; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize - 1; }

    void push(const T &item){
        tab[tail] = item;
        tail = (tail + 1) % msize;            
    }                             // dodanie na koniec
    void push(T &&item){
        assert(!full());
        head = (head + msize -1) % msize;
        tab[head] = std::move(item);
    }                                  // dodanie na koniec
    T &front() { return tab[head]; }                      // zwraca początek
    T &back() { return tab[(tail + msize - 1) % msize]; } // zwraca koniec
    void pop(){
        assert(!empty());
        head = (head+1)%msize;
    }                                           // usuwa początek
    void clear(){
        assert(!empty());
        for (int i = head; i != tail; i = (i + 1) % msize)
        {
            pop();
        }
        delete[] tab;
        tab = nullptr;
        head = 0;
        tail = 0;
        msize = 0;
    }                                         // czyszczenie listy z elementów
    void display(){
         for (int i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
    }
};