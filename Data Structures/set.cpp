#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

class LinkedListSet {
private:
    Node* head;

    Node* sortedInsert(Node* sorted, Node* newNode) {
        if (sorted == nullptr || newNode->value <= sorted->value) {
            newNode->next = sorted;
            return newNode;
        } else {
            sorted->next = sortedInsert(sorted->next, newNode);
            return sorted;
        }
    }

    void insertionSort() {
        Node* sorted = nullptr;
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next; // Save next for the next iteration
            sorted = sortedInsert(sorted, current);
            current = next;
        }
        head = sorted;
    }

    
    bool find(int value, Node* current) {
        /*while (current != nullptr) {
            if (current->value == value) return true;
            current = current->next;
        }*/
        if(current != nullptr){
            if(current->value == value) return true;
            current = current->next;
            return find(value, current);
        }
        return false;
    }

    Node* addRecursive(Node* node, int value) {
        if (node == nullptr) {
            Node* newNode = new Node(value);
            newNode->next = node;
            return newNode;
        }
        if(node->value == value){
            return head;
        }
        if (value < node->value) {
            Node* newNode = new Node(value);
            newNode->next = node;
            return newNode;
        }else if(node->value == value){
            return node;
        }
        else {
            node->next = addRecursive(node->next, value);
        }
        return node;
    }

    Node *removeRecursive(Node *node, int value){
        if (node == nullptr)
            return nullptr;
        if (node->value == value){
            Node *tempNext = node->next;
            delete node;
            return removeRecursive(tempNext, value);
        }
        else{
            node->next = removeRecursive(node->next, value);
            return node;
        }
    }

    void print(Node* head) {
        Node* current = head;
        /*while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }*/
        if(current != nullptr){ 
            cout << current->value << " ";
            print(current->next);
        }
        return;
    }

    

    
public:
    ~LinkedListSet(){
        Node *current = head;
        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

     LinkedListSet() : head(nullptr) {}

    bool find(int value){
        return find(value, head);
    }
    void remove(int value){
        head = removeRecursive(head, value);
    }
    void print(){
        print(head);
        cout << endl;
    }
    void add(int value){
        //cout<< head->value << endl;
        head = addRecursive(head, value);
    }

    /*LinkedListSet* unionSet(LinkedListSet& other) {
    LinkedListSet* result = new LinkedListSet();
    Node *current1 = this->head, *current2 = other.head;
    
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->value < current2->value) {
            result->add(current1->value);
            current1 = current1->next;
        } else if (current1->value > current2->value) {
            result->add(current2->value);
            current2 = current2->next;
        } else {
            result->add(current1->value);
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    
    // Add remaining elements
    while (current1 != nullptr) {
        result->add(current1->value);
        current1 = current1->next;
    }
    while (current2 != nullptr) {
        result->add(current2->value);
        current2 = current2->next;
    }
    
    return result;
    }*/
    void unionSetRecursive(Node* current1, Node* current2, LinkedListSet* result) {
    if (current1 == nullptr && current2 == nullptr) return;

    if (current1 != nullptr && (current2 == nullptr || current1->value < current2->value)) {
        result->add(current1->value);
        unionSetRecursive(current1->next, current2, result);
    } else if (current2 != nullptr && (current1 == nullptr || current1->value > current2->value)) {
        result->add(current2->value);
        unionSetRecursive(current1, current2->next, result);
    } else if (current1 != nullptr && current2 != nullptr) {
        result->add(current1->value); 
        unionSetRecursive(current1->next, current2->next, result);
    }
}

    LinkedListSet* unionSet(LinkedListSet& other) {
        LinkedListSet* result = new LinkedListSet();
        this.insertionSort();
        other.insertionSort();
        unionSetRecursive(this->head, other.head, result);
        return result;
    }


    /*LinkedListSet* intersection(LinkedListSet& other) {
    LinkedListSet* result = new LinkedListSet();
    Node *current1 = this->head, *current2 = other.head;
    
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->value == current2->value) {
            result->add(current1->value);
            current1 = current1->next;
            current2 = current2->next;
        } else if (current1->value < current2->value) {
            current1 = current1->next;
        } else {
            current2 = current2->next;
        }
    }
    
    return result;
    }*/

    void intersectionRecursive(Node* current1, Node* current2, LinkedListSet* result) {
        if (current1 == nullptr || current2 == nullptr) return;

        if (current1->value == current2->value) {
            result->add(current1->value);
            intersectionRecursive(current1->next, current2->next, result);
        } else if (current1->value < current2->value) {
            intersectionRecursive(current1->next, current2, result);
        } else {
            intersectionRecursive(current1, current2->next, result);
        }
    }

    LinkedListSet* intersection(LinkedListSet& other) {
        LinkedListSet* result = new LinkedListSet();
        this.insertionSort();
        other.insertionSort();
        intersectionRecursive(this->head, other.head, result);
        return result;
    }


    /*LinkedListSet* difference(LinkedListSet& other) {
    LinkedListSet* result = new LinkedListSet();
    Node *current1 = this->head, *current2 = other.head;
    
    while (current1 != nullptr) {
        while (current2 != nullptr && current2->value < current1->value) {
            current2 = current2->next;
        }
        
        if (current2 == nullptr || current1->value < current2->value) {
            result->add(current1->value);
        }
        
        current1 = current1->next;
    }
    
    return result;
    }*/

    void differenceRecursive(Node *current1, Node *current2, LinkedListSet *result){
        if (current1 == nullptr)
            return;

        while (current2 != nullptr && current2->value < current1->value){
            current2 = current2->next;
        }
        if (current2 == nullptr || current1->value < current2->value){
            result->add(current1->value);
        }
        differenceRecursive(current1->next, current2, result);
    }

    LinkedListSet *difference(LinkedListSet &other){
        LinkedListSet *result = new LinkedListSet();
        this.insertionSort();
        other.insertionSort();
        differenceRecursive(this->head, other.head, result);
        return result;
    }
};

int main() {
    LinkedListSet set1;
    set1.add(1);
    set1.add(2);
    set1.add(3);

    LinkedListSet set2;
    set2.add(3);
    set2.add(7);
    set2.add(4);
    set2.add(5);

    cout << "Set 1: ";
    set1.print();
    cout << "Set 2: ";
    set2.print();

    set2.remove(7);
    cout << "Remove(7), Set 2: ";
    set2.print();

    LinkedListSet* unionSet = set1.unionSet(set2);
    cout << "Union: ";
    unionSet->print();
    delete unionSet;

    LinkedListSet* intersectionSet = set1.intersection(set2);
    cout << "Intersection: ";
    intersectionSet->print();
    delete intersectionSet;

    LinkedListSet* differenceSet = set1.difference(set2);
    cout << "Difference (Set 1 - Set 2): ";
    differenceSet->print();
    delete differenceSet;

    return 0;
}

