#include <iostream>
#include <vector>
#include <array>
#include <exception>

using std::vector;
using std::array;

int adjustIndex(int id) { return id; }

template<int N>
struct MultiStack {

    struct StackInfo {
        int start, size, capacity;

        StackInfo(int s = 0, int c = 0): start(s), capacity(c)
        { }

        bool isWithinStachCapacity(int index)
        {
            if (index < 0 || index >= values.size())
            {
                return false;
            }

            int contiguousIndex = index < start ? values.size() : index;
        }

        int lastCapacityIndex()
        {
            return adjustIndex(start + capacity -1);
        }

        int lastElementIndex()
        {
            return adjustIndex(start + size - 1);
        }

        bool isFull() { return size == capacity; }
        bool isEmpty() { return size == 0; }
    };


    array<StackInfo, N> info;
    vector<int> values;
    
    MultiStack(int defaultSize = 10)
    {
        for (int i = 0; i < N; ++i)
        {
            info[i] = StackInfo(defaultSize * i, defaultSize);
        }

        values.reserve(N * defaultSize);
    }

    void push(int stackNum, int value)
    {
        if (allStacksAreFull())
        {
            throw std::exception("StackAreFull");
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
            throw std::exception("Stak is empty");
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
        return numberOfElements() == values.size();
    }

    int adjustIndex(int index)
    {
        int max = values.size();
        return ((index % max) + max) % max;
    }

    int nextIndex(int index)
    {
        return adjustIndex(index+1);
    }

    int previousIndex(int index)
    {
        return adjustIndex(index - 1);
    }

};


int main() {
    MultiStack<3> ms;
}
