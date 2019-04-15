#include <iostream>
#include "stack.hpp"
#include "stack_policy.hpp"

using std::cout, std::cerr, std::endl, std::cin;
using base_t = int;



int main()
{
    std::ios_base::sync_with_stdio(false);

    stack<base_t, std_vector_adapt<base_t>> _stack;

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
