#include <iostream>
#include<vector>
#include "priorityqueue.h"

int main()
{

    MyPriorityQueue<int> queue;

    for(int i = 0; i < 3; i++){
        queue.push(i+1);
    }
    std::cout << "Qeque poczatkowa:"
              << std::endl;
    queue.display();

    queue.push(2);
    std::cout << "\nQeque, push(2): " << std::endl;
    queue.display();

    queue.push(5);
    std::cout << "\nQeque, push(5): " << std::endl;
    queue.display();


    int rozmiar = queue.size();
    std::cout <<"\nAktualny rozmiar queue: " << rozmiar << std::endl;

    int max_el = queue.top();
    std::cout <<"\nNajwiekszy element: " << max_el << std::endl;

    MyPriorityQueue<int> emptyQueue;
    std::cout << "\nCzy emptyQueue jest empty? " << (emptyQueue.empty() ? "Yes" : "No") << std::endl;

    MyPriorityQueue<int> firstOtherQueue(queue);
    std::cout<<"\ncopy contuctor: "<<std::endl;
    std::cout << "queue: " << std::endl;
    queue.display();
    std::cout << "\nfirstOtherQueue :" <<std::endl;
    firstOtherQueue.display();

    MyPriorityQueue<int> secondOtherQueue(std::move(firstOtherQueue));
    std::cout << "\n\nmove contuctor: "<< std::endl;
    std::cout << "firstOtherQueue: " << std::endl;
    firstOtherQueue.display();
    std::cout << "\nsecondOtherQueue :"<< std::endl;
    secondOtherQueue.display();

    secondOtherQueue = queue;
    std::cout << "\n\ncopy operator=: "<< std::endl;
    std::cout << "queue: " << std::endl;
    queue.display();
    std::cout << "\nsecondOtherQueue :" << std::endl;
    secondOtherQueue.display();

    MyPriorityQueue<int> lastQueue;
    lastQueue.push(1);
    lastQueue.push(2);
    lastQueue.push(3);

    lastQueue = std::move(secondOtherQueue);
    std::cout << "\n\nmove operator=: "<< std::endl;
    std::cout << "secondOtherQueue: " << std::endl;
    secondOtherQueue.display();
    std::cout << "\nlastQueue:" << std::endl;
    lastQueue.display();

    lastQueue.clear();
    std::cout<<"\n\nlastQueue: "<<std::endl;
    lastQueue.display();
    std::cout<<"\nPowyzej nic nie ma bo to jest sprawdzanie poprawnosci dzialania clear()"<<std::endl;

}