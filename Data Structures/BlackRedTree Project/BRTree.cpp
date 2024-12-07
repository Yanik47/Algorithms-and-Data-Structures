#include "BRTree.h"
#include <iostream>
#include <ostream>
#include <thread>
#include <chrono>

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree()
{
    
    // tworzymy lisc
    sentinel = new Node<Key, Value>();
    sentinel->color = BLACK;
    sentinel->parent = nullptr;
    sentinel->left = nullptr;
    sentinel->right = nullptr;
    root = sentinel;
}

template <typename Key, typename Value>
RedBlackTree<Key, Value>::~RedBlackTree()
{
    //liscie sa reprezentowane w postaci jednego elementu w pamieci na 
    //ktore maja wskazniki wszystki ostatnie wezly(lub wezly ktore maja jednego potomka)
    //sentinel jest czarny
    destroyTree(root);
    delete sentinel;
    delete root;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::destroyTree(Node<Key, Value> *node)
{
    //usuwamy poki nie trafilismy na liscie
    if (node != sentinel){
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key &key, const Value &value)
{
    //inicjalizacja nowego wezla, na poczatku nie ma rodzicow, a potomki jego to liscie
    //nowy wezlel zawsze czerwony
    Node<Key, Value> *new_node = new Node<Key, Value>();
    new_node->key = key;
    new_node->value = value;
    new_node->color = RED;
    setColor(new_node, RED);
    new_node->left = sentinel;
    new_node->right = sentinel;
    new_node->parent = nullptr;

    // metoda dla umisczenia wezla
    insertNode(root, new_node);

    //jezeli osciec - korzen, robimy wezel czarnym  
    if(new_node->parent == nullptr){
        setColor(new_node, BLACK);
    }
    //jezeli ojcec nie jest korzeniem i diadek nie jest korzeniem robimy balansowanie
    else if(!(new_node->parent->parent == nullptr)){
        insertFixup(new_node);
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insertNode(Node<Key, Value> *&root, Node<Key, Value> *new_node)
{
    Node<Key, Value> *parent = nullptr;
    Node<Key, Value> *current = root;


    // szukamy miejsce na wezel, reguly takie same jak u drzewa binarnego
    while (current != sentinel)
    {
        parent = current;
        if (new_node->key < current->key)
        {
            current = current->left;
        }
        else if(new_node->key > current->key)
        {
            current = current->right;
        }
        
    }

    //dodajemy wskaznik na rodzica
    new_node->parent = parent;

    // wyjasmiamy czy wezel jest lewym czy prawym potomkiem rodzica i dodajemy wskaznik rodzicowi na potomka
    if (parent == nullptr)
    {
        root = new_node; //jezeli jest pusty wezel robimy root-em
    }
    else if (new_node->key < parent->key)
    {
        parent->left = new_node;
    }
    else
    {
        parent->right = new_node;
    }

}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insertFixup(Node<Key, Value> *node)
{
    //poki ojciec wezla jest czernowy robimy balansowanie, w petli idziemy rekurencyjnie do gory, az do root-a
    //musimy rozpatrywac 5 roznych przypadkow balansowania
    while (getColor(node->parent) == RED)
    {
        //jezeli osciec jest lewym potomkiem dziadka
        if (node->parent == node->parent->parent->left)
        {
            //tworzymy wujka
            Node<Key, Value> *uncle = node->parent->parent->right;

            //jezeli wujek istnieje i jest czerwony
            if (uncle != nullptr && getColor(uncle) == RED)
            {
                // Case 1: wujek i ojciec na czarno, a dziadek na czerwono

                setColor(node->parent, BLACK);
                setColor(uncle, BLACK);
                setColor(node->parent->parent, RED);
                node = node->parent->parent;
            }
            //jezeli wujka nie ma lub jest czarny
            else
            {
                //oraz wezel jest prawym potomkiem rodzica 
                if (node == node->parent->right)
                {
                    // Case 2: zamieniamy wezel na ojca i robimy obrot w lewo
                    node = node->parent;
                    rotateLeft(node);
                }

                // Case 3: jezeli wezel nie jest prawym potomkiem ojca 
                //dziadek na czerwono, ojciec na czarno i obrot wokol dziadka wprawo
                setColor(node->parent->parent, RED);
                setColor(node->parent, BLACK);
                rotateRight(node->parent->parent);
            }
        }
        //jezeli ojciec to prawy potomek dziaka
        else
        {
            //Case 4 i 5 sa analogiczne, roznica tylko w symetrii odnosci dziaka
            Node<Key, Value> *uncle = node->parent->parent->left;

            if (uncle != nullptr && getColor(uncle) == RED)
            {
                setColor(node->parent, BLACK);
                setColor(uncle, BLACK);
                setColor(node->parent->parent, RED);
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    rotateRight(node);
                }

                setColor(node->parent, BLACK);
                node->parent->parent->color = RED;
                setColor(node->parent->parent, RED);
                rotateLeft(node->parent->parent);
            }
        }
        //root jest czarny, nie trzeba go farbowac
        if(node == root){
            break;
        }
    }
    

    setColor(root, BLACK); // pro wszelki wypadek robimy root czarnym
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rotateLeft(Node<Key, Value> *node)
{
    //Operacja "rotacji w lewo" polega na zmianie struktury drzewa, aby poprawic jego rownowage
    //rodzic prawego dziecka staje sie jego lewym dzieckiem 
    //jezeli mamy prawego potomka mozemy dokonac operacji bo nie mamy potrzeby
    if (node == nullptr || node->right == nullptr)
        return;
    //wyznaczamy prawego potomka
    Node<Key, Value> *right_child = node->right;
    //poddrzewo zostanie przeniesione na miejsce node
    node->right = right_child->left;
    //jezeli w poddrzewie jest cos oprocz lisci aktualizujemy wskaznik potomka node na nowego rodzica
    if (right_child->left != sentinel)
        right_child->left->parent = node;
    //aktualizujemy rodzica potomka 
    right_child->parent = node->parent;
    //jezeli rodzica nie ma, to mamy do czynienia z root-em 
    if (node->parent == nullptr)
        root = right_child;

    //jesli wezel jest lewym potomkiem, prawe dziecko wezla bedzie lewym dzieckim ojca  
    else if (node == node->parent->left)
        node->parent->left = right_child;
    else
    //i na odwrot 
        node->parent->right = right_child;

    //aktualizacja pozycji wezla w drzewie po rotacji i wskaznika na rodzica wezla 
    right_child->left = node;
    node->parent = right_child;
}

//symetryczna dla rotateLeft
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rotateRight(Node<Key, Value> *node)
{
    if (node == nullptr || node->left == nullptr)
        return;

    Node<Key, Value> *left_child = node->left;
    node->left = left_child->right;

    if (left_child->right != sentinel)
        left_child->right->parent = node;

    left_child->parent = node->parent;

    if (node->parent == nullptr)
        root = left_child;
    else if (node == node->parent->left)
        node->parent->left = left_child;
    else
        node->parent->right = left_child;

    left_child->right = node;
    node->parent = left_child;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::remove(const Key &key)
{
    Node<Key, Value> *nodeToRemove = findNode(key);

    if (nodeToRemove == sentinel || nodeToRemove == nullptr)
        return; // nie mamy takiego wezla

    // przed usuwaniem musimy zapamietac kolor
    Node<Key, Value> *child, *copyRemNode;
    copyRemNode = findNode(key);

    Color original_color = getColor(copyRemNode);

    /*Color child_color_left = BLACK;
    Color child_color_right = RED;

    if(nodeToRemove->left != sentinel)
        child_color_left = getColor(nodeToRemove->left);
    if(nodeToRemove->right !=sentinel)
        child_color_right = getColor(nodeToRemove->right);*/

    //Jezeli mamy jednego potomka i to jest prawy potomek
    if (nodeToRemove->left == sentinel)
    {
        /*if(original_color == BLACK){
            std::cout<<"right"<<std::endl;
        }*/
        //wartosc do balansowania ustawiamy na prawe dziecko usuwanej wartosci
        child = nodeToRemove->right;
        //zamieniamy miejscami usuwana wartosc i prawego potomka tej wartosci 
        transplant(nodeToRemove, nodeToRemove->right);
    }
    //Jezeli mamy jednego potomka i jest to lewy potomek 
    else if (nodeToRemove->right == sentinel)
    {
        //std::cout<<"cps2"<<std::endl;
        //symetrycznie dla prawego potomka 
        child = nodeToRemove->left;
        transplant(nodeToRemove, nodeToRemove->left);
    }
    //Usuwana wartosc ma dwu potomkow 
    else
    {
        //std::cout<<node_to_remove->right->left<<std::endl;
        //musimy znalezc najmniejszego potomka usuwanej wartosci w prawym poddrzewie 
        Node<Key, Value> *successor = minimumNode(nodeToRemove->right);

        /*bool red = successor->color == RED;
        if(red){
        std::cout<< "true" <<std::endl;}*/

        //tak jak wczesniej musimy zapamietac kolor zamieniajacego wezla 
        original_color = getColor(successor);
        //wezlem balansujacym drzewo bedzie prawe dziecko zamieniajacego wezla
        child = successor->right;

        //jezeli zamieniajacy wezel jest dzieckiem usuwanego wezla, wezlem do balansowania bedzie zamieniajacy wezel
        if(successor->parent == nodeToRemove){

            child->parent = successor;

        }
        // w przeciwnym wypadku zamieniamy miejscamy wezly zamieniajacego wezla i jego prawego dziecka 
        //i uwzgledniamy wskazniki. Jest to potrzebne dlatego, ze na miejscu zamieniajacego wezla pozniej
        //sie okaze wezel do usuniecia i zeby dzieci zamieniajacego wezla nie mieli ->parent == nullptr;
        else{

            transplant(successor, successor->right);

            successor->right = nodeToRemove->right;
 
            successor->right->parent = successor;

        }
        //zamieniamy miejscami wezly do zamiany i usuniecia, uwzgledniamy wskazniki
        transplant(nodeToRemove, successor);
        successor->left = nodeToRemove->left;
        successor->left->parent = successor;
        setColor(successor, getColor(nodeToRemove));



    }
    //usuwamy wezel
    delete nodeToRemove;
    //jezeli zostal usuniety czarny wezel dokonujemy balansowania 
    if(original_color == BLACK){
        removeFixup(child, false);
    
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::transplant(Node<Key, Value> *DelNode, Node<Key, Value> *SwapNode)
{
    // jezeli DelNode to root zapisujemy tam SwapNode
    if (DelNode->parent == nullptr)
        root = SwapNode;
    //jezeli DelNode jest rodzicem SwapNode uwzgledniamy wskaznik na dziecko
    else if (DelNode == DelNode->parent->right)
        DelNode->parent->right = SwapNode;
    else
        DelNode->parent->left = SwapNode;
    //uwzgledniamy wskaznik na rodzica 
    SwapNode->parent = DelNode->parent;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::removeFixup(Node<Key, Value> *node, bool isChildFree)
{
    //nie mozemy zmieniac  koloru root-a, zamiana koloru czerwonego wezla nie zmiana balansu drzewa i konczy balansowanie
    while (node != root && getColor(node) == BLACK) 
    {

        //przypadek dla lewego dziecka
        if (node == node->parent->left) 
        {
            //wyznaczam brata, on jest kluczowy dla balansowania w przypadku usuwania wezla z drzewa 
            Node<Key, Value> *sibling = node->parent->right;
            //case 1 brat jest czerwony
            if (getColor(sibling) == RED) 
            {
                //farbujemy brata  na czarno, ojca na czerwono, rotacja w lewo i brat musi nadal byc sprawa 
                setColor(sibling, BLACK);
                setColor(node->parent, RED);
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }
            //Czarny brat ma dzieci i one sa czarne 
            if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK)
            {
                //brat musi byc czerwony i jego ojciec zostaje bratem
                setColor(sibling, RED);
                node = node->parent;
            } 
            else 
            {
                //brat jest czarny ale dzieci nie sa czarne 
                if (getColor(sibling->right) != RED) 
                {
                    //jezeli lewe dziecko brata jest czerwonym, robimy z niego czarnego, a z brata czerwonego
                    setColor(sibling->left, BLACK);
                    setColor(sibling, RED);
                    //dokonujemy rotacji wprawo i brat musi byc prawym dzieckiem rodzica 
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }
                else{
                //prawy jest czerwonym 
                //farbujemy brata w kolor rodzica, rodzica na czarno, dziecko brata na czarno 
                //i rotacja w lewo
                //wezel zostaje root-em
                setColor(sibling, getColor(node->parent));
                setColor(node->parent, BLACK);
                setColor(sibling->right, BLACK);
                rotateLeft(node->parent);
                node = root;
            }
            
        } 
        }
        //przypadek do prawego dzicka jest analogiczny 
        else 
        {
            Node<Key, Value> *sibling = node->parent->left;
            if (getColor(sibling) == RED) 
            {
                setColor(sibling, BLACK);
                setColor(node->parent, RED);
                rotateRight(node->parent);
                sibling = node->parent->left;
            }
            
            if (getColor(sibling->right) == BLACK && getColor(sibling->left) == BLACK) 
            {
                setColor(sibling, RED);
                node = node->parent;
            } 
            else 
            {
                if (getColor(sibling->left) == BLACK) 
                {
                    setColor(sibling->right, BLACK);
                    setColor(sibling, RED);
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                else{
                setColor(sibling, getColor(node->parent));
                setColor(node->parent, BLACK);
                setColor(sibling->left, BLACK);
                rotateRight(node->parent);
                node = root;}
            }
            
        }
    }
    setColor(node, BLACK);
}
//zeby sie nie zgubic we wskaznikach dodalismy set-ry oraz get-ry

//ustawia kolor
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::setColor(Node<Key, Value> *node, Color color)
{
    if (node == sentinel)
        return;
    node->color = color;
}
//zwraca kolor
template <typename Key, typename Value>
Color RedBlackTree<Key, Value>::getColor(Node<Key, Value> *node)
{
    if (node == sentinel)
        return BLACK;
    return node->color;
}

//minimum jest analogiczny jak w drzewie binarnym
template <typename Key, typename Value>
Node<Key, Value> *RedBlackTree<Key, Value>::minimumNode(Node<Key, Value> *node)
{   
    if(node->left == 0){
        return node;
    }

    while (node->left != sentinel)
        node = node->left;
    return node;
}
//display jest preorder, jest najprostzy dla weryfikacji poprawnosci wyniku
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::display()
{
    if (root == nullptr)
        return;

    displayPreOrder(root);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::displayPreOrder(Node<Key, Value> *node)
{
    if (node == sentinel)
        return;

    //Wypisywanie klucza
    std::cout << "Key: " << node->key << ", Value: " << node->value << ", Color: " << (node->color == RED ? "RED" : "BLACK") << std::endl;

    //prawe poddrzewo
    displayPreOrder(node->left);
std::this_thread::sleep_for(std::chrono::milliseconds(50));
    //lewe podrzewo
    displayPreOrder(node->right);
}

template <typename Key, typename Value>
int RedBlackTree<Key, Value>::myHeight( Node<Key, Value> *root){
    
    if (root == nullptr) {
        return 0;
    } else {
        int leftHeight = myHeight(root->left);
        int rightHeight = myHeight(root->right);  
        return std::max(leftHeight, rightHeight)+1;
    }

}

template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::isEmpty(){

return root == getSentinel();
}

template <typename Key, typename Value>
Node<Key, Value> *RedBlackTree<Key, Value>::getSentinel()
{
    return sentinel;
}