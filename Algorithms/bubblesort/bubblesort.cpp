#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <cassert>
#include <algorithm>

template <typename T>
bool operator<(const T &lhs, const T &rhs)
{
    return lhs < rhs;
}

template <typename Container>
void anysort(Container &container)
{
    auto current = container.begin();
    auto next = std::next(current);
    auto end = container.end();
    bool swapped = true;
    while(swapped == true)
    {   swapped = false;
        
        while(next != end)
        {   
            std::cout << "Current: "<<*current << " ";
            std::cout << "Next: " <<*next << " ";
            std::cout << std::endl;
            if (*next < *current)
            {
                std::swap(*next, *current);
                swapped = true;
            }
//**************************************************************************
            std::cout<< "tablica po kroku sortowania:" << " ";
            auto current2 = container.begin();
            while(current2 != end){    
                
                std::cout <<*current2 << " ";
                ++current2;
            }
                std::cout << std::endl;
//***************************************************************************
            ++next;
            ++current;
        }
    current = container.begin();
    next = std::next(current);
    --end;
    }
}

int main()
{
    std::vector<int> intVector = {8, 5, 2, 9, 1, 4, 3, 6};
    anysort(intVector);
    std::cout << std::endl;
    std::cout << "Sprawdzenie sortowania przez assert(is_sorted(...)): ";
    std::cout << std::endl;
    assert( std::is_sorted(intVector.begin(), intVector.end())); 
    for (const int &value : intVector)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::array<double, 5> doubleArray = {3.2, 1.7, 2.5, 0.5, 4.8};
    anysort(doubleArray);
    std::cout << std::endl;
    std::cout << "Sprawdzenie sortowania przez assert(is_sorted(...)): ";
    std::cout << std::endl;
    assert( std::is_sorted(std::begin(doubleArray), std::end(doubleArray)));
    for (const double &value : doubleArray)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::list<std::string> stringList = {"banana", "apple", "cherry", "date", "fig"};
    anysort(stringList);
    std::cout << std::endl;
    std::cout << "Sprawdzenie sortowania przez assert(is_sorted(...)): ";
    std::cout << std::endl;
    assert( std::is_sorted(stringList.begin(), stringList.end()) );
    for (const std::string &value : stringList)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}