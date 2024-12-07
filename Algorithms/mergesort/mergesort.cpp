#include <iostream>
#include <vector>
#include <array>
#include <vector> 
#include <cassert>
#include <algorithm>

template <typename T>
bool operator > (const T &lhs, const T &rhs)
{
    return lhs > rhs;
}
template<typename T>
std::vector<T> merge(const std::vector<T> &left, const std::vector<T> &right) {
    std::vector<T> result;
    size_t leftIndex = 0, rightIndex = 0;

    while (leftIndex < left.size() && rightIndex < right.size()) {
        if (left[leftIndex] > right[rightIndex]) {
            result.push_back(right[rightIndex]);
            rightIndex++;
        } else {
            result.push_back(left[leftIndex]);
            leftIndex++;
        }
    }

    while (leftIndex < left.size()) {
        result.push_back(left[leftIndex]);
        leftIndex++;
    }

    while (rightIndex < right.size()) {
        result.push_back(right[rightIndex]);
        rightIndex++;
    }

    return result;
}
template<typename T>
std::vector<T> mergeSort(std::vector<T> &vec){

    if(vec.size() <= 1){
         return vec;
    }
    else{
        int half = vec.size()/2;

        std::vector<T> left(vec.begin(), vec.begin() + half);
        std::vector<T> right(vec.begin()+ half, vec.end());

     return merge(mergeSort(left), mergeSort(right));

    }
}

int main(){

    std::vector<int> a = {1, 9, 3, 4, 7, 6, 2, 8, 5};
    a = mergeSort(a);
    std::cout << std::endl;
    std::cout << "Sprawdzenie sortowania przez assert(is_sorted(...)): ";
    std::cout << std::endl;
    assert( std::is_sorted(a.begin(), a.end())); 
    for (const int &value : a) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    std::vector <double> b = {3.2, 1.7, 2.5, 0.5, 4.8};
    b = mergeSort(b);
    std::cout << std::endl;
    std::cout << "Sprawdzenie sortowania przez assert(is_sorted(...)): ";
    std::cout << std::endl;
    assert( std::is_sorted(b.begin(), b.end())); 
    for (const double &value : b)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}