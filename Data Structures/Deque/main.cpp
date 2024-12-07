#include <iostream>
#include "mydeque.h"

int main() {

    MyDeque<int> deque;

    for(int i = 0; i < 3; i++){
    deque.push_back(i+1);}
    std::cout << "Deque poczatkowa: \n"<< std::endl;
    deque.display();
    std::cout << "tail(gdzie): " << deque.gdzietail() << std::endl;
    std::cout << "tail: " << deque.czymJestTail() << std::endl;
    std::cout << "head: " << deque.czymJestHead() << std::endl;

    deque.push_front(2);
    std::cout << "\n Deque, push_back(2): \n "<< std::endl;
    deque.display();
    std::cout << "tail(gdzie): " << deque.gdzietail() << std::endl;
    std::cout << "tail: " << deque.czymJestTail() << std::endl;
    std::cout << "head: " << deque.czymJestHead() << std::endl;

    deque.push_front(5);
    std::cout << "\n Deque, push_back(3): \n "<< std::endl;
    deque.display();

    std::cout << "tail(gdzie): " << deque.gdzietail() << std::endl;
    std::cout << "tail: " << deque.czymJestTail() << std::endl;
    std::cout << "head: " << deque.czymJestHead() << std::endl;
    std::cout << "Max size: "<< deque.max_size() << std::endl;
    deque.insert(2, 5);
    std::cout << "\n Deque, insert(3, 5): \n "<< std::endl;
    deque.display();

    int max_rozmiar = deque.max_size();
    int rozmiar = deque.size();
    std::cout << "Maksymalny rozmiar deque: " << max_rozmiar << " aktualny rozmiar: " << rozmiar << std::endl;
    
    int f_el = deque.front();
    int l_el = deque.back();
    std::cout << "\nPierwszy element deque: " << f_el <<" Ostatni element deque: "<< l_el<< std::endl;
    
    deque.pop_front();
    f_el = deque.front();
    std::cout << "\nPierwszy element listy po funkcji pop_front(): " << f_el << std::endl;

    std::cout << "Deque: \n"<< std::endl;
    deque.display();

    deque.pop_back();
    l_el = deque.back();
    std::cout << "\nOstatni element listy po funkcji pop_back(): " << f_el << std::endl;
    deque.display();


    /*deque.insert(5, 9);
    int index = deque.index(9);
    std::cout << "index: " << index << std::endl;
    if (index != -1) {
        deque.insert(index, 9);
        std::cout << "Deque po wstawieniu wartosci 9 funkcja insert(5, 9) " << index << ": " << std::endl;

    } else {
        std::cout << "Element nie znaleziony w liscie." << std::endl;
    }*/

    std::cout << "\nDeque: \n"<< std::endl;
    deque.display();

    int element = deque[1];
    std::cout << "Wartosc elementa przypisanego z deque[1]: " << element << std::endl;

    deque[3] = 10;
    std::cout << "Deque po przypisaniu wartosci 10 do list[3]: "<< std::endl;
    deque.display();

    deque.erase(1);
    std::cout << "\nDeque po usunieciu pierwszego elementu erase(1): "<< std::endl;
    deque.display();


    MyDeque<int> emptyDeque;
    std::cout << "Czy emptyDeque jest empty? " << (emptyDeque.empty() ? "Yes" : "No") << std::endl;

    MyDeque<int> fullDeque(3);
    fullDeque.push_back(1);
    fullDeque.push_back(2);
    fullDeque.push_back(3);
    std::cout << "Czy fulldeque jest pelna? " << (fullDeque.full() ? "Yes" : "No") << std::endl;
    std::cout << "fullDeque przed wypelnieniem fullDeque = deque" << std::endl;
    fullDeque.display();
    fullDeque = std::move(deque);
    
    std::cout << "fullDeque po wypelnieniu fullDeque = deque: "<< std::endl;
    fullDeque.display();
    std::cout << "Deque: \n"<< std::endl;
    deque.display();
    
    MyDeque<int> copyDeque = fullDeque;
    MyDeque<int> moveDeque = std::move(fullDeque);

    std::cout << " copyDeque po wypelnieniu copyDeque = fullDeque \ncopyDeque1 po wypelnieniu copyDeque1 = fullDeque: " << std::endl; 
    copyDeque.display();
    moveDeque.display();

    MyDeque <int> moveDeque_konstr(std::move(moveDeque));
    std::cout << "moveDeque_konstr po wypelnieniu moveDeque_konstr(std::move(moveDeque)): " << std::endl;  
    moveDeque_konstr.display();
    moveDeque_konstr.clear();


    return 0;
}
