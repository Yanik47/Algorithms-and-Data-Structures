#ifndef STACK_H
#define STACK_H 

#include <vector>
#include <iostream>
#include<stack>

template <typename T>
class MyStack {
    std::vector<T> lst;
public:
    MyStack(int s=10) { lst.reserve(s); } // default constructor
    ~MyStack() { lst.clear(); }

    MyStack(const MyStack& other) : lst(other.lst) {} // copy constructor
    MyStack(MyStack&& other) : lst(std::move(other.lst)) {}// move constructor
    MyStack& operator=(const MyStack& other){
        if(this == &other){
            return *this;
        }
        lst = other.lst;
        return *this;
    } // copy assignment operator, return *this
    MyStack& operator=(MyStack&& other){
        if(this == &other){
            return *this;
        }
        lst = std::move(other.lst);
        return *this;
    } // move assignment operator, return *this

    bool empty() const { return lst.empty(); } // checks if the container has no elements
    bool full() const { return lst.size() == lst.capacity(); }
    int size() const { return lst.size(); }
    int max_size() const { return lst.capacity(); }
    void push(const T& item) { lst.push_back(item); }
    void push(T&& item) { lst.push_back(std::move(item)); }
    T& top() { return lst.back(); } // zwraca koniec, nie usuwa
    void pop() { lst.pop_back(); } // usuwa koniec
    void clear() { lst.clear(); }
    void display()const{
        for(const auto& item : lst){
            std::cout << item <<  " ";
        }
        std::cout << std::endl;
    }
};
#endif
