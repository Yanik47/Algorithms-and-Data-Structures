#include <iostream>
#include <algorithm>
#include <utility>

template <typename ValueType, typename PriorityType, size_t Size>
class MyPriorityQueue
{
    using ValuePair = std::pair<ValueType, PriorityType>;
    ValuePair lst[Size];
    size_t currentSize = 0;

private:
    void push_heap(size_t start, size_t end)
    {
        int childIdx = end - 1;
        int parentIdx;

        while (childIdx > start)
        {
            parentIdx = (childIdx - 1) / 2;
            if (lst[parentIdx].second < lst[childIdx].second)
            {
                std::swap(lst[parentIdx], lst[childIdx]);
                childIdx = parentIdx;
            }
            else
            {
                break;
            }
        }
    }

    void pop_heap(size_t start, size_t end)
    {
        if (start == end)
            return;

        std::swap(lst[start], lst[end - 1]);
        size_t heapEnd = end - 1;

        size_t parentIdx = start;

        while (true)
        {
            size_t leftChildIdx = 2 * parentIdx + 1;
            size_t rightChildIdx = 2 * parentIdx + 2;
            size_t largestIdx = parentIdx;

            if (leftChildIdx < heapEnd && lst[leftChildIdx].second > lst[largestIdx].second)
            {
                largestIdx = leftChildIdx;
            }

            if (rightChildIdx < heapEnd && lst[rightChildIdx].second > lst[largestIdx].second)
            {
                largestIdx = rightChildIdx;
            }

            if (largestIdx == parentIdx)
                break;

            std::swap(lst[parentIdx], lst[largestIdx]);
            parentIdx = largestIdx;
        }
    }

public:
    MyPriorityQueue() = default;
    ~MyPriorityQueue() = default;

    bool empty() const { return currentSize == 0; }
    size_t size() const { return currentSize; }
    bool isFull() const { return currentSize == Size; }

    void push(const ValuePair &item)
    {
        if (isFull())
        {
            throw std::runtime_error("Priority queue is full");
        }
        lst[currentSize++] = item;
        push_heap(0, currentSize);
    }

    void push(ValuePair &&item)
    {
        if (isFull())
        {
            throw std::runtime_error("Priority queue is full");
        }
        lst[currentSize++] = std::move(item);
        push_heap(0, currentSize);
    }

    ValuePair &top()
    {
        if (empty())
        {
            throw std::runtime_error("Priority queue is empty");
        }
        return lst[0];
    }

    void pop()
    {
        if (empty())
        {
            throw std::runtime_error("Priority queue is empty");
        }
        pop_heap(0, currentSize--);
    }

    void clear() { currentSize = 0; }

    void display()
    {
        for (size_t i = 0; i < currentSize; ++i)
        {
            std::cout << "(" << lst[i].first << ", " << lst[i].second << ") ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    MyPriorityQueue<int, int, 10> pq;
    pq.push({1, 5});
    pq.push({2, 2});
    pq.push({3, 8});

    pq.display();

    while (!pq.empty())
    {
        auto top = pq.top();
        std::cout << "Top: (" << top.first << ", " << top.second << ")\n";
        pq.pop();
    }

    return 0;
}
