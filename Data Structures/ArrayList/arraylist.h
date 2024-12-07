// arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
class ArrayList {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
public:
    ArrayList(int s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor

    ~ArrayList() { delete [] tab; } // destruktor

    ArrayList(const ArrayList& other){ // copy constructor
        msize = other.msize;
        assert(msize>0);
        last = other.last;

        tab = new T[msize];
        for(int i = 0; i < msize; i++){
            tab[i] = other.tab[i];
        }
    }
    // usage:   ArrayList<int> list2(list1);

    ArrayList(ArrayList&& other){ // move constructor NIEOBOWIAZKOWE

        msize = other.msize;
        last = other.last;
        assert(other.tab == nullptr);
        tab = other.tab;
        other.tab = nullptr;

    }
    // usage:   ArrayList<int> list2(std::move(list1));

    ArrayList& operator=(const ArrayList& other){ // copy assignment operator, return *this

        if (this == &other) {
        return *this;
    }


    if (msize < other.last) {

        delete[] tab;
        msize = other.msize;
        tab = new T[msize];
        assert(tab != nullptr);
    }

    last = other.last;

    for (int i = 0; i < last; i++) {
        tab[i] = other.tab[i];
    }

    return *this;
    }// usage:   list2 = list1;

    ArrayList& operator=(ArrayList&& other){ // move assignment operator, return *this

    if (this == &other) {
        return *this;
    }
    delete[] tab;
    msize = other.msize;
    tab = new T[msize];
    tab = other.tab;
    last = other.last;

    other.tab = nullptr;
    other.msize = 0;
    other.last = 0;

    return *this;
    }// usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return last == 0; } // checks if the container has no elements+
    bool full() const { return last == msize; } // checks if the container is full+
    int size() const { return last; } // liczba elementow na liscie+
    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow+
    void push_front(const T& item){
        if(last >= msize){
            int new_size = msize + 1;
            T* n_tab = new T[new_size];
            for(int i = 0; i<last; i++){
                n_tab[i+1] = tab[i];
            }
            n_tab[0] = item;
            last++;
            delete[] tab;
            msize = new_size;
            tab = new T[msize];
            for(int i = 0; i<last; i++){
                tab[i] = n_tab[i];
            }
            delete[]n_tab;
            new_size = 0;

        }
        else{
        for (int i = last; i > 0; i--) {
            tab[i] = tab[i - 1];
        }
        tab[0] = item;
        last++;
        }
    } // dodanie na poczatek+
    void push_front(T&& item){
        if(last >= msize){
            int new_size = msize + 1;
            T* n_tab = new T[new_size];
            for(int i = 0; i<last; i++){
                n_tab[i+1] = std::move(tab[i]);
            }
            n_tab[0] = std::move(item);
            last++;
            delete[] tab;
            msize = new_size;
            tab = new T[msize];
            for(int i = 0; i<last; i++){
                tab[i] = std::move(n_tab[i]);
            }
            delete[]n_tab;
            new_size = 0;

        }
        else{
        for (int i = last; i > 0; i--) {
            tab[i] = std::move(tab[i - 1]);
        }
        tab[0] = std::move(item);
        last++;
        }
    } // dodanie na poczatek NIEOBOWIAZKOWE+
    void push_back(const T& item){
        if(last >= msize){
            int new_size = msize + 1;
            T* n_tab = new T[new_size];
            for(int i = 0; i<last; i++){
                n_tab[i] = tab[i];
            }
            n_tab[last] = item;
            last++;
            delete[] tab;
            msize = new_size;
            tab = new T[msize];
            for(int i = 0; i<last; i++){
                tab[i] = n_tab[i];
            }
            delete[]n_tab;
            new_size = 0;

        }
        else{
        tab[last] = item;
        last++;
        }
    } // dodanie na koniec+
    void push_back(T&& item){
        if(last >= msize){
            int new_size = msize + 1;
            T* n_tab = new T[new_size];
            for(int i = 0; i<last; i++){
                n_tab[i] = std::move(tab[i]);
            }
            n_tab[last] = std::move(item);
            last++;
            delete[] tab;
            msize = new_size;
            tab = new T[msize];
            for(int i = 0; i<last; i++){
                tab[i] = std::move(n_tab[i]);
            }
            delete[]n_tab;
            new_size = 0;

        }
        else{
        tab[last] = std::move(item);
        last++;
        }
    } // dodanie na koniec NIEOBOWIAZKOWE+
    T& front(){
        assert(last != 0);
        return tab[0];
    } // zwraca poczatek, nie usuwa, error dla pustej listy+
    T& back(){
        assert(last != 0);
        return tab[last-1];
    }// zwraca koniec, nie usuwa, error dla pustej listy+
    void pop_front(){
        assert(last != 0);
    if (last > 0) {
        for (int i = 1; i < last; i++) {
            tab[i - 1] = tab[i];
        }

        last--;
    }
} // usuwa poczatek, error dla pustej listy+
    void pop_back(){
        assert(last != 0);
    if (last > 0) {
        last--;
    }
} // usuwa koniec, error dla pustej listy+
    void clear(){
    for(int i = 0; i < last; i++){
        tab[i] = T();
    }
    //tab = (T)0;
    last = 0;
} // czyszczenie listy z elementow+
    void display() {
    for (int i = 0; i < last; i++) {
        std::cout << tab[i] << " ";
        if(i == 4){
            std::cout<<"\n"<<" ";
        }
    }
    std::cout << std::endl;
} // lepiej zdefiniowac operator<<+
    void reverse(){
        for(int i = 0; i < last/2; i++){
            T temp = tab[last-1-i];
            tab[last-1-i] = tab[i];
            tab[i] = temp;
        }
    } // odwracanie kolejnosci+
    void sort(){
        for (int i = 0; i < last - 1; i++) {
            for (int j = 0; j < last - i - 1; j++) {
                if (tab[j] > tab[j + 1]) {
                    T temp = tab[j];
                    tab[j] = tab[j + 1];
                    tab[j + 1] = temp;
                }
            }
        }
    } // sortowanie listy
 
    void merge(ArrayList& other){
        if(msize - last < other.last){
            msize += other.last;
            T* n_tab = new T[msize];

            for(int i = 0; i < last; i++) {
                n_tab[i] = tab[i];
            }
            delete[] tab;

            tab = n_tab;
        }
            int j = 0;
            for(int i = last; i < last + other.last; i++) {
            tab[i] = other.tab[j];
            j++;
            last += other.last;
            other.last = 0;
            }
        }//  merges two sorted lists into one NIEOBOWIAZKOWE

    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator+
    T& operator[](int pos){
        assert(pos>=0&&pos<last);
        return tab[pos];
    } // podstawienie L[pos]=item, odczyt L[pos]+
    const T& operator[](int pos) const{
        assert(pos>=0&&pos<last);
        return tab[pos];
    } // dostep do obiektu const+
    void erase(int pos){
        assert(pos>=0&&pos<last);
        last--;
        for (int i = pos; i < last; i++) {
        tab[i] = tab[i + 1];
    }
  } // usuniecie elementu na pozycji pos+
    int index(const T& item){
        for(int i = 0; i < last; i++) {
        if (tab[i] == item) {
            return i;
        }
    }
    return -1;
  } // jaki index na liscie (-1 gdy nie ma)+
    void insert(int pos, const T& item){
        assert(pos>=0&&pos<last);
        if(last >= msize){
            int new_size = msize + 2;
            T* n_tab = new T[new_size];
            for(int i = 0; i<pos; i++){
                n_tab[i] = tab[i];
            }
            n_tab[pos] = item;
            for(int i = pos; i<last; i++){
                n_tab[i+1] = tab[i];
            }
            last++;
            delete[] tab;
            msize = new_size;
            tab = new T[msize];
            for(int i = 0; i<last; i++){
                tab[i] = n_tab[i];
            }
            delete[]n_tab;
            new_size = 0;

        }
        else{
        for (int i = last; i > pos; i--) {
            tab[i] = tab[i - 1];
        }
        tab[pos] = item;
        last++;
        }

    } // inserts item before pos
    void insert(int pos, T&& item){
        assert(pos>=0&&pos<last);
        if(pos == 0){
            push_front(item);
        }
        else if(pos == last){
            push_back(item);
        }
        else{
            if(last >= msize){
                int new_size = msize + 2;
                T* n_tab = new T[new_size];
                for(int i = 0; i<pos; i++){
                    n_tab[i] = std::move(tab[i]);
                }
                n_tab[pos] = std::move(item);
                for(int i = pos; i<last; i++){
                    n_tab[i+1] = std::move(tab[i]);
                }
                last++;
                delete[] tab;
                msize = new_size;
                tab = new T[msize];
                for(int i = 0; i<last; i++){
                    tab[i] = std::move(n_tab[i]);
                }
                delete[]n_tab;
                new_size = 0;

            }
        else{
        for (int i = last; i > pos; i--) {
            tab[i] = std::move(tab[i-1]);
        }
        tab[pos] = std::move(item);
        last++;
        }

    }
    }
      // inserts item before pos
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

// EOF
