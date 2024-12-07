#include <iostream>
#include "doublelist.h"

int main()
{
    DoubleList<int> list;
    for (int i = 0; i < 8; i++)
    {
        list.push_front(i + 1);
    }
    std::cout << "Wartosci listy: ";
    list.display();
    std::cout << std::endl;
    list.push_back(9);
    std::cout << "Wartosci listy po push_back(9): ";
    list.display();
    std::cout << std::endl;
    list.insert(3, 1);
    std::cout << "Wartosci listy po insert(3, 5): ";
    list.display();
    std::cout << std::endl;
    int rozmiar = list.size();
    std::cout << "Rozmiar listy : " << rozmiar << std::endl;

    std::cout << "Aktualny rozmiar: " << rozmiar << std::endl; 

    list.pop_front();
    std::cout << "Wartosci listy po pop_front(): ";
    list.display();
    std::cout << std::endl;

    int f_el = list.front();
    std::cout << "Pierwszy element listy po funkcji front(): " << f_el << std::endl;

    int b_el = list.back();
    std::cout << "Ostatni element listy po funkcji back(): " << b_el << std::endl;

    std::cout << "Metoda wypisywania wartosci przez funkcje display" << std::endl;
    list.display();
    std::cout << std::endl;

    std::cout << "Odwrocona lista: ";
    list.display_reversed();
    std::cout << std::endl;

    list.pop_back();
    std::cout << "Lista po usunieciu ostatniego elementu pop_back(): ";
    list.display();
    std::cout << std::endl;

    list.insert(4, 5);
    int index = list.index(5);
    std::cout << "index: " << index << std::endl;
    if (index != -1)
    {
        list.insert(index, 4);
        std::cout << "Lista po wstawieniu wartosci 4 funkcja insert " << index << ": ";
        list.display();
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Element nie znaleziony w liscie." << std::endl;
    }

    int element = list[1];
    std::cout << "Wartosc elementa przypisanego z list[1]: " << element << std::endl;

    list[3] = 10;
    std::cout << "Lista po przypisaniu wartosci 10 do list[3]: ";
    list.display();
    std::cout << std::endl;

    list.erase(1);
    std::cout << "Lista po usunieciu 1 erase(1): ";
    list.display();
    std::cout << std::endl;

    DoubleList<int> emptyList;
    std::cout << "Czy empty lista jest empty? " << (emptyList.empty() ? "Yes" : "No") << std::endl;

    DoubleList<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
    std::cout << "list2 przed wypelnieniem list2 = list: ";
    list2.display();
    std::cout << std::endl;
    //list2=list;
    std::cout << "list2 po wypelnieniu list2 = list: ";
    list2.display();
    std::cout << "lista: ";
    list.display();
    std::cout << std::endl;
    std::cout << "lista2 po clear(): ";
    std::cout << std::endl;
    list2.clear();
    list2.display();
    

    return 0;
}

