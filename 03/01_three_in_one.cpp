#include <iostream>
#include <vector>
#include <array>
#include <exception>

using std::vector;
using std::array;
using std::cout, std::cerr, std::endl;

int adjustIndex(int index, int maxvalue)
{
    return ((index % maxvalue) + maxvalue) % maxvalue;
}

template<int N>
struct MultiStack {

    struct StackInfo {
        int max_index;
        int start, size, capacity;

        StackInfo(int v = 0, int s = 0, int c = 10):
            max_index(v), start(s), size(0), capacity(c)
        { 
        }

        StackInfo& operator = (StackInfo const& v)
        {
            this->max_index = v.max_index;
            this->start = v.start;
            this->size = v.size;
            this->capacity = v.capacity;
        }

        bool isWithinStachCapacity(int index)
        {
            if (index < 0 || index >= max_index)
            {
                return false;
            }

            int const contiguousIndex = index < start ? max_index : index;
            int const end = start + capacity;

            return start <= contiguousIndex && contiguousIndex < end;
        }

        int lastCapacityIndex()
        {
            return ::adjustIndex(start + capacity -1, max_index);
        }

        int lastElementIndex()
        {
            return ::adjustIndex(start + size - 1, max_index);
        }

        bool isFull() { return size == capacity; }
        bool isEmpty() { return size == 0; }

        friend std::ostream& operator << (std::ostream& os, StackInfo const& v) {
            return os << v.max_index << ' ' << v.start << ' ' << v.size << ' ' << v.capacity;
        }
    };

    array<StackInfo, N> info;
    vector<int> values;
    


    MultiStack(int defaultSize = 10)
    {
        auto const max_index = N * defaultSize;
        for (int i = 0; i < N; ++i)
        {
            info[i] = StackInfo(max_index, defaultSize * i, defaultSize);
        }

        values = vector<int>(max_index);
    }

    void push(int stackNum, int value)
    {
        if (allStacksAreFull())
        {
            throw std::runtime_error("StackAreFull");
        }

        StackInfo& stack = info[stackNum];
        if (stack.isFull())
        {
            expand(stackNum);
        }

        stack.size++;
        values[stack.lastElementIndex()] = value;
    }


    int pop(int stackNum)
    {
        StackInfo& stack = info[stackNum];
        if (stack.isEmpty())
        {
            throw std::runtime_error("Stak is empty");
        }

        int value = values[stack.lastElementIndex()];
        values[stack.lastElementIndex()] = 0;
        stack.size--;
        return value;
    }


    int peek(int stackNum)
    {
        StackInfo& stack = info[stackNum];
        return values[stack.lastElementIndex()];
    }


    void shift(int stackNum)
    {
        StackInfo& stack = info[stackNum];

        if (stack.size >= stack.capacity)
        {
            int nextStack = (stackNum + 1) % info.size();
            shift(nextStack);
            stack.capacity++;
        }

        int index = stack.lastCapacityIndex();

        cout << index << endl;

        while (stack.isWithinStachCapacity(index))
        {
            values[index] = values[previousIndex(index)];
            index = previousIndex(index);
        }

        values[stack.start] = 0;
        stack.start = nextIndex(stack.start);
        stack.capacity--;
    }

    void expand(int stackNum)
    {
        shift((stackNum+1)%info.size());
        info[stackNum].capacity++;
    }

    int numberOfElements()
    {
        int size = 0;
        for (StackInfo& sd : info)
        {
            size += sd.size;
        }

        return size;
    }


    bool allStacksAreFull()
    { 
        return numberOfElements() && numberOfElements() == values.size();
    }

    int adjustIndex(int index)
    {
        return ::adjustIndex(index, values.size());
    }

    int nextIndex(int index)
    {
        return adjustIndex(index+1);
    }

    int previousIndex(int index)
    {
        return adjustIndex(index - 1);
    }


    friend std::ostream& operator << (std::ostream& os, MultiStack const& ms)
    {
        os << ms.values.size() << endl;
        for (auto const v: ms.values)
        {
            os << v << ' ' ;
        }

        return os;
    }
};


int main() {
    MultiStack<3> ms;

    ms.push(0, 1);
    ms.push(0, 2);
    ms.push(0, 3);
    ms.push(0, 4);
    ms.push(0, 5);
    ms.push(0, 6);
    ms.push(0, 7);
    ms.push(0, 8);
    ms.push(0, 9);
    ms.push(0, 10);
    ms.push(0, 11);
    cout << ms.peek(0) << endl;
    ms.push(1, 3);
    cout << ms.peek(1) << endl;
    ms.push(2, 4);
    cout << ms.peek(2) << endl;
    ms.pop(0);
    cout << ms.peek(0) << endl;
    cout << ms << endl;

}
