
#include <iostream>
//#include "BRTree.h"
#include "BRTree.cpp"

int main() {
    RedBlackTree<int, std::string> tree;

    // Вставка элементов в дерево
    tree.insert(5, "A");
    tree.insert(10, "B");
    tree.insert(7, "C");
    tree.insert(15, "D");
    tree.insert(11, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");
    tree.insert(25, "I");
    tree.insert(20, "J");
    tree.insert(22, "K");
    tree.insert(2, "L");
    tree.insert(1, "M");
    tree.insert(21, "N");
    tree.insert(8, "O");
    tree.insert(6, "P");    
    tree.insert(17, "R");
    tree.insert(9, "S");
    std::cout << "Pre-order traversal of the tree:" << std::endl;
    tree.display();

    // szukanie elementu
    int key_to_find = 7;
    std::string* found_value = tree.find(key_to_find);
    if (found_value != nullptr) {
        std::cout << "Found value for key " << key_to_find << ": " << *found_value << std::endl;
    } else {
        std::cout << "Key " << key_to_find << " not found in the tree." << std::endl;
    }
    

    // usuwanie elementu, test balansowania
    int len = 9;
    int key_to_remove[len] = {15, 7, 5, 18, 17, 25, 20, 22, 21};
    for(int i = 0; i < len; i++){
        tree.remove(key_to_remove[i]);
        std::cout << "\nPre-order traversal of the tree after removing key " << key_to_remove[i] << ":" << std::endl;
        tree.display();
    }

    Node<int, std::__cxx11::basic_string<char>> *root = tree.getRoot();
    Node<int, std::__cxx11::basic_string<char>> *minimum = tree.getMinimum();
    bool empty = tree.isEmpty();
    int height = tree.treeHeight();
    std::cout<<"Root: " << root->value << "\nMinimum: " << minimum->value << "\nTree is empty:" << (empty ?"Yes":"No")<< "\nHeight(height root = 1): "<< height<<std::endl;


    return 0;
}
