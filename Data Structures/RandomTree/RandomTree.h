// Szablon dla węzła drzewa binarnego i drzewa BST.

#include <cstdlib>
#include <iostream>
#include <queue>
#include <cassert>
#include <stack>
template <typename T>
struct BSTNode
{
    // the default access mode and default inheritance mode are public
    T value;
    int height;
    BSTNode *left, *right;
    // BSTNode *parent;   // używane w pewnych zastosowaniach
    //  kostruktor domyślny
    BSTNode() : value(T()), height(0), left(nullptr), right(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T &item) : value(item), height(0), left(nullptr), right(nullptr) {}
    ~BSTNode() {} // destruktor
};

template <typename T>
struct Tree
{
    T max;
    T min;
    int height;
    int il_leafs;
    int il_nodes;
    int sum;
    bool liczby;

    Tree(): max(-10e7), min(10e7), height(0), il_leafs(0), il_nodes(0), sum(0), liczby(false) {}
    Tree(const T &root) : max(root), min(root), height(0), il_leafs(0), il_nodes(0), sum(0) {} 
    ~Tree() {};
};

// Szablon dla przypadkowego drzewa binarnego.
template <typename T>
class RandomBinaryTree
{
    BSTNode<T> *root;
    Tree<T> tree;

public:
    RandomBinaryTree() : root(nullptr) {} // konstruktor domyślny
    ~RandomBinaryTree() { clear(); }      // trzeba wyczyścić
    bool empty() const { return root == nullptr; }
    T &top()
    {
        assert(root != nullptr);
        return root->value;
    } // podgląd korzenia
    void insert(const T &item) { root = insert(root, item); }
    // void remove(const T& item); // na razie nie usuwamy elementów
    //  Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T *search(const T &item) const
    {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    T *find_min(){return &tree.min;}
    T *find_max(){return &tree.max;}
    int calc_leafs(){return tree.il_leafs;}
    int calc_nodes(){return tree.il_nodes;}
    int calc_nodes_v2(){return tree.il_nodes+tree.il_leafs;}
    int calc_total(){return tree.sum;}
    int calc_height(){return tree.height;}
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void preorder_iter();
    void liczby(bool liczby){tree.liczby = liczby;}
    BSTNode<T> *getRoot() const{return root;}
    void iter_preorder();
    void iter_inorder();   // trudne
    void iter_postorder(); // trudne
    void bfs();            // przejście poziomami (wszerz)
    void clear(){
        clear(root);
        tree.min = 10e7;
        tree.max = -10e7;
        tree.height = 0;
        tree.liczby = false;
        tree.sum = 0;
        tree.il_leafs = 0;
        tree.il_nodes = 0;
        root = nullptr;
    }
    void display() { display(root, 0); }

    void preorder_rek(BSTNode<T> *node, int height)
    {

        if (node == nullptr){
            return;
        }

        visit(node);
        if (node->value < tree.min){
            tree.min = node->value;
        }
        if (node->value > tree.max){
            tree.max = node->value;
        }
        if (node->left == nullptr && node->right == nullptr){
            tree.il_leafs++;
            tree.height = std::max(tree.height, height);
        }
        else{
            tree.il_nodes++;
        }
        if (tree.liczby){
            tree.sum += node->value;
        }
        preorder_rek(node->left, height + 1);
        preorder_rek(node->right, height + 1);
    }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    void clear(BSTNode<T> *node){
        if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
    }
    BSTNode<T> *insert(BSTNode<T> *node, const T &item); // zwraca nowy korzeń
    BSTNode<T> *search(BSTNode<T> *node, const T &item) const;
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node)
    {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
};

// Wyświetlanie obróconego (counterclockwise) drzewa binarnego.
template <typename T>
void RandomBinaryTree<T>::display(BSTNode<T> *node, int level)
{
    if (node == nullptr)
        return;
    display(node->right, level + 1);
    std::cout << std::string(3 * level, ' ') << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
void RandomBinaryTree<T>::bfs()
{
    if (root == nullptr)
        return;
    std::queue<BSTNode<T> *> Q; // wskaźniki do wezłów
    BSTNode<T> *node = root;
    Q.push(node);
    while (!Q.empty())
    {
        node = Q.front(); // podglądamy
        Q.pop();          // usuwamy z kolejki
        visit(node);      // tu jest właściwe przetworzenie węzła
        if (node->left != nullptr)
            Q.push(node->left);
        if (node->right != nullptr)
            Q.push(node->right);
    }
}

template <typename T>
BSTNode<T> *RandomBinaryTree<T>::insert(BSTNode<T> *node, const T &item)
{
    if (node == nullptr)
    {
        return new BSTNode<T>(item);
    }
    if (std::rand() % 2)
    { // można lepiej
        node->left = insert(node->left, item);
    }
    else
    {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzen
}

template <typename T>
BSTNode<T> *RandomBinaryTree<T>::search(BSTNode<T> *node, const T &item) const
{
    if (node == nullptr || node->value == item)
    {
        return node;
    }
    T *ptr;
    ptr = search(node->left, item);
    if (ptr == nullptr)
    {
        ptr = search(node->right, item);
    }
    return ptr;
}

template <typename T>
void RandomBinaryTree<T>::inorder(BSTNode<T> *node)
{
    if (node == nullptr)
        return;
    inorder(node->left);
    visit(node);
    inorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::preorder(BSTNode<T> *node)
{
    if (node == nullptr)
        return;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::postorder(BSTNode<T> *node)
{
    if (node == nullptr)
        return;
    postorder(node->left);
    postorder(node->right);
    visit(node);
}

template <typename T>
void RandomBinaryTree<T>::preorder_iter()
{
    if (root == nullptr){
        tree.min = 0;
        tree.max = 0;
        return;
    }
    std::stack<std::pair<BSTNode<T> *, int>> S; // wskaźniki do węzłów
    BSTNode<T> *node = root;
    int height = 0;
    S.push({node, height});
    while (!S.empty())
    {
        auto [currentNode, currentHeight] = S.top(); // podglądamy
        S.pop();        // usuwamy ze stosu
        visit(currentNode);    // tu jest właściwe przetworzenie węzła
        if (currentNode->value < tree.min)
            tree.min = currentNode->value;
        if (currentNode->value > tree.max)
            tree.max = currentNode->value;
        if (currentNode->left == nullptr && currentNode->right == nullptr)
            tree.il_leafs++;
        else
            tree.il_nodes++;
        tree.height = std::max(tree.height, currentHeight);
        if (tree.liczby)
            tree.sum += currentNode->value;
        if (currentNode->right != nullptr) // najpierw prawe poddrzewo!
            S.push({currentNode->right, currentHeight+1});
        if (currentNode->left != nullptr)
            S.push({currentNode->left, currentHeight+1});

        tree.height = std::max(tree.height, currentHeight);
    }
}

template <typename T>
void RandomBinaryTree<T>::iter_preorder()
{
    if (root == nullptr)
        return;
    std::stack<BSTNode<T> *> S; // wskaźniki do węzłów
    BSTNode<T> *node = root;
    S.push(node);
    while (!S.empty())
    {
        node = S.top();             // podglądamy
        S.pop();                    // usuwamy ze stosu
        visit(node);                // tu jest właściwe przetworzenie węzła

        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
        if (node->left != nullptr)
            S.push(node->left);
    }
}






