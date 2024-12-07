#include <iostream>
#include "arraylist.h"

int main() {

    ArrayList<int> list;
    for(int i = 0; i < 8; i++){
    list.push_front(i+1);}
    list.push_back(2);
    list.insert(3, 5);
    int max_rozmiar = list.max_size();
    int rozmiar = list.size();

    std::cout << "Wartosci listy: " << list << std::endl;

    std::cout << "Maksymalny ozmiar listy: " << max_rozmiar << " aktualny rozmiar: " << rozmiar << std::endl;
    
    int f_el = list.front();
    int l_el = list.back();
    std::cout << "Pierwszy element listy: " << f_el <<" Ostatni element listy: "<< l_el<< std::endl;
    list.pop_front();
    f_el = list.front();
    std::cout << "Pierwszy element listy po funkcji front(): " << f_el << std::endl;

    std::cout << "Alternatywna metoda wypisywania wartosci przez funkcje display" << std::endl;
    list.display();

    list.reverse();
    std::cout << "Odwrocona lista: " << list << std::endl;

    list.sort();
    std::cout << "Sortowana lista: " << list << std::endl;

    list.pop_back();
    std::cout << "Lista po usunieciu ostatniego elementu pop_back(): " << list << std::endl;

    list.insert(3, 5);
    int index = list.index(5);
    std::cout << "index: " << index << std::endl;
    if (index != -1) {
        list.insert(index, 4);
        std::cout << "List po wstawieniu wartosci 4 funkcja insert " << index << ": " << list << std::endl;
    } else {
        std::cout << "Element nie znaleziony w liscie." << std::endl;
    }

    int element = list[1];
    std::cout << "Wartosc elementa przypisanego z list[1]: " << element << std::endl;

    list[3] = 10;
    std::cout << "Lista po przypisaniu wartosci 10 do list[3]: " << list << std::endl;

    list.erase(1);
    std::cout << "Lista po usunieciu pierwszego elementu erase(1): " << list << std::endl;


    ArrayList<int> emptyList;
    std::cout << "Czy empty lista jest empty? " << (emptyList.empty() ? "Yes" : "No") << std::endl;

    ArrayList<int> fullList(3);
    fullList.push_back(1);
    fullList.push_back(2);
    fullList.push_back(3);
    std::cout << "Czy pelna lista jest pelna? " << (fullList.full() ? "Yes" : "No") << std::endl;
    //merge()
    std::cout << "fullList przed wypelnieniem fullList = list" << fullList << std::endl;
    fullList = list;
    std::cout << "fullList po wypelnieniu fullList = list: " << fullList << "list: "<< list<< std::endl;
    ArrayList<int> mergeList(2);

    mergeList.push_back(1);
    mergeList.push_back(4);
    std::cout << "Wartosci mergelisty: " << mergeList << std::endl;
    list.pop_back();
    list.pop_back();
    
    list.merge(mergeList);
    std::cout << "Wartosci listy(przed tym dwa razy wylowana funkcja pop_back()) po scalaniu: " << list << std::endl;
    fullList.clear();


    return 0;
}
