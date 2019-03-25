//g++ std=c++17 -Wall -Wextra -pedantic -pipe  -O2 %  && echo 1 2 -3 2 3 4 |
//./.aout
#include <iostream>
#include "stack.hpp"
using std::cout, std::cerr, std::endl, std::cin;

using base_t = int;
using stack_t = stack_min<base_t>;

int main()
{
    std::ios_base::sync_with_stdio(false);

    stack_t s;

    base_t v;
    while (cin >> v)
    {
        s.push(v);
    }

    cout << s.min() << endl;

    return 0;
}
