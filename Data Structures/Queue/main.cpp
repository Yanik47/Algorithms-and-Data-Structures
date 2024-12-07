#include <iostream>
#include "myqueue.h"

int main()
{

    MyQueue<int> queue;

    for (int i = 0; i < 3; i++)
    {
        queue.push(i + 1);
    }
    std::cout << "Qeque poczatkowa: \n"
              << std::endl;
    queue.display();

    queue.push(2);
    std::cout << "\n Qeque, push(2): \n " << std::endl;
    queue.display();

    queue.push(5);
    std::cout << "\n Qeque, push(3): \n " << std::endl;
    queue.display();


    int max_rozmiar = queue.max_size();
    int rozmiar = queue.size();
    std::cout << "Maksymalny rozmiar queue: " << max_rozmiar << " aktualny rozmiar: " << rozmiar << std::endl;

    int f_el = queue.front();
    int l_el = queue.back();
    std::cout << "\nPierwszy element queue: " << f_el << " Ostatni element queue: " << l_el << std::endl;

    queue.pop();
    f_el = queue.front();
    std::cout << "\nPierwszy element kolejki po funkcji pop(): " << f_el << std::endl;
    std::cout << "Queue: \n"<< std::endl;
    queue.display();

    MyQueue<int> emptyQueue;
    std::cout << "Czy emptyQueue jest empty? " << (emptyQueue.empty() ? "Yes" : "No") << std::endl;

    MyQueue<int> fullQueue(3);
    fullQueue.push(1);
    fullQueue.push(2);
    fullQueue.push(3);
    std::cout << "Czy fullqueue jest pelna? " << (fullQueue.full() ? "Yes" : "No") << std::endl;
    std::cout << "fullQueue przed wypelnieniem fullQueue = queue" << std::endl;
    fullQueue.display();
    fullQueue = std::move(queue);

    std::cout << "fullQueue po wypelnieniu fullQueue = queue: " << std::endl;
    fullQueue.display();
    std::cout << "Queue: \n"
              << std::endl;
    queue.display();

    MyQueue<int> copyQueue = fullQueue;
    MyQueue<int> moveQueue = std::move(fullQueue);

    std::cout << " copyDeque po wypelnieniu copyQueue = fullQueue \ncopyQueue po wypelnieniu copyQueue = fullQueue: " << std::endl;
    copyQueue.display();
    moveQueue.display();

    MyQueue<int> moveQueue_konstr(std::move(moveQueue));
    std::cout << "moveQueue_konstr po wypelnieniu moveQueue_konstr(std::move(moveQueue)): " << std::endl;
    moveQueue_konstr.display();
    moveQueue_konstr.clear();

    return 0;
}
