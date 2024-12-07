#include <iostream>
#include "RandomTree.h"
int main()
{

    std::cout << "Teraz test czesci rekurencyjnej\n" << std::endl;
    RandomBinaryTree<int> tree;
    tree.liczby(true);
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.preorder_rek(tree.getRoot(), 0);

    std::cout << "\nMin dla rekurencujnego: " << *tree.find_min() << std::endl;
    std::cout << "Max dla rekurencyjnego: " << *tree.find_max() << std::endl;
    std::cout << "Ilosc lisci dla rekurencyjnego: " << tree.calc_leafs() << std::endl;
    std::cout << "Ilosc wezlow dla rekurencyjnego(jezeli liscie nie sa wezlami): " << tree.calc_nodes() << std::endl;
    std::cout << "Ilosc wezlow dla rekurencyjnego(jezeli liscie sa wezlami): " << tree.calc_nodes_v2() << std::endl;
    std::cout << "Total sum: " << tree.calc_total() << std::endl;
    std::cout << "Tree height(liczymy od 1): " << tree.calc_height() << std::endl;

    std::cout << "\nPreorder przejscie: ";
    tree.preorder();
    std::cout << std::endl;

    tree.clear();

    std::cout <<"A tutaj juz test czesci iteracyjnej\n" <<std::endl;
    RandomBinaryTree<int> tree1;
    tree1.liczby(true);
    tree1.insert(50);
    tree1.insert(30);
    tree1.insert(70);
    tree1.insert(20);
    tree1.insert(40);
    tree1.insert(60);
    tree1.insert(80);

    tree1.preorder_iter();
    std::cout << "\nMin dla iteracyjnego: " << *tree1.find_min() << std::endl;
    std::cout << "Max dla iteracyjnego: " << *tree1.find_max() << std::endl;
    std::cout << "Ilosc lisci dla iteracyjnego: " << tree1.calc_leafs() << std::endl;
    std::cout << "Ilosc wezlow dla iteracyjnego(jezeli liscie nie sa wezlami): " << tree1.calc_nodes() << std::endl;
    std::cout << "Ilosc wezlow dla iteracyjnego(jezeli liscie sa wezlami): " << tree.calc_nodes_v2() << std::endl;
    std::cout << "Total sum: " << tree1.calc_total() << std::endl;
    std::cout << "Tree height(liczymy od 1): " << tree1.calc_height() << std::endl;

    std::cout << "\nPreorder przejscie: ";
    tree1.preorder();
    std::cout << std::endl;

    tree.clear();

    return 0;
}