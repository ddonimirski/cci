// 
#include <iostream>
#include <vector>
#include <array>
#include <exception>

using std::vector;
using std::array;
using std::cout, std::endl, std::cin;


template<class T, int SIZE = 10>
struct stack_plate
{
    vector<array<T, SIZE>> plate;

    vector<size_t> tops;
    int cur_stack;

    stack_plate()
        :cur_index({-1, -1})
    {}

    bool empty() const 
    {
        return cur_index.top < 0;
    }

    void push(T&& v)
    {
        if (cur_index.stack < 0 || cur_index.top == SIZE-1)
        {
            array<T, SIZE> arr;

            if (plate.size() == 0 || cur_index.top == SIZE-1)
            {
                plate.push_back(arr);
                cur_index.fullfill.push_back(0)
            }

            cur_index.stack++;
            cur_index.top = 0;
        }

        else
        {
            cur_index.top++;
            cur_index.sizes[cur_index.stack]++;
        }

        plate[cur_index.stack][cur_index.top] = v;
    }

    void popAt(int id)
    {
        if (id > cur_index.stack)
        {
            throw std::runtime_error("out of range");
        }

        if (

    }

    T const& top() const
    {
        if (empty())
        {
            throw std::runtime_error("empty stack_plate 2");
        }

        return plate[cur_index.stack][cur_index.top];
    }

    void pop()
    {
        if (empty() || cur_index.stack < 0)
        {
            throw std::runtime_error("empty stack_plate");
        }

        if (cur_index.top == 0 && cur_index.stack > 0)
        {
            cur_index.stack--;
            cur_index.top = SIZE-1;
        }

        else
        {
            cur_index.top--;
        }
    }
};

int main()
{
    stack_plate<int> s;

    s.push(10);
    cout << s.top() << endl;
    s.push(20);
    cout << s.top() << endl;
    s.push(30);
    cout << s.top() << endl;
    s.push(40);
    cout << s.top() << endl;
    s.push(50);
    cout << s.top() << endl;
    s.push(60);
    cout << s.top() << endl;
    s.push(70);
    cout << s.top() << endl;
    s.push(80);
    cout << s.top() << endl;
    s.push(90);
    cout << s.top() << endl;
    s.push(100);
    cout << s.top() << endl;
    s.push(110);
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    s.push(1);
    cout << s.top() << endl;
}
