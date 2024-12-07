enum Color { RED, BLACK };

template <typename Key, typename Value>
struct Node {
    Key key;
    Value value;
    Node* parent;
    Node* left;
    Node* right;
    Color color;
};

template <typename Key, typename Value>
class RedBlackTree {
public:


    RedBlackTree();//+
    ~RedBlackTree();//+

    void insert(const Key& key, const Value& value);//+
    void remove(const Key& key);//+
    Node<Key, Value>* getRoot(){
    return root;
    }
    Node<Key, Value>* getMinimum(){
        return minimumNode(root);
    }
    bool isEmpty();
    int treeHeight(){
        return myHeight(root)-1;
    }

    Value* find(const Key& key){
    Node<Key, Value> *node = findNode(key);

    if (node != nullptr)
        return &(node->value);
    else
        return nullptr;
    }//+
    void display();

private:
    Node<Key, Value>* root;
    Node<Key, Value> *sentinel;


    void rotateLeft(Node<Key, Value>* node);//+
    void rotateRight(Node<Key, Value>* node);//+
    void insertFixup(Node<Key, Value>* node);//+
    void removeFixup(Node<Key, Value>* node, bool isChildFree);//+
    void setColor(Node<Key, Value> *node, Color color);
    Color getColor(Node<Key, Value> *node);

    Node<Key, Value>* findNode(const Key& key){
    Node<Key, Value> *current = root;

    while (current != nullptr)
    {
        if (key == current->key)
            return current;
        else if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    return nullptr; 
    }//+
    Node<Key, Value>* minimumNode(Node<Key, Value>* node);
    void transplant(Node<Key, Value>* u, Node<Key, Value>* v);//+
    void deleteNode(Node<Key, Value>* node);
    void destroyTree(Node<Key, Value> *node);
    void insertNode(Node<Key, Value> *&root, Node<Key, Value> *new_node);
    void displayPreOrder(Node<Key, Value> *node);
    Node<Key, Value> *getSentinel();
    int myHeight(Node<Key, Value> *root);
};



