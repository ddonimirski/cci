#include <iostream>
#include "stack.hpp"
#include "vector.hpp"

using std::cout, std::cerr, std::endl, std::cin;
using base_t = int;

int main()
{
    std::ios_base::sync_with_stdio(false);

    stack<base_t, vector<base_t>> _stack;

    base_t v;

    while (cin>>v)
    {
        _stack.push(v);
    }

    while (!_stack.empty())
    {
        cout << _stack.top() << endl;
        _stack.pop();
    }

    return 0;
}
