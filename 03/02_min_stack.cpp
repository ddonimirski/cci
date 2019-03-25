//g++ std=c++17 -Wall -Wextra -pedantic -pipe  -O2 %  && echo 1 2 -3 2 3 4 |
//./.aout
#include <iostream>
#include <limits>
#include "stack.hpp"
using std::cout, std::cerr, std::endl, std::cin;

using base_t = int;
static constexpr base_t MAX_BASE = std::numeric_limits<base_t>::max();

// it's posible to keep stack of struct { T value; T min; }
// or better :P

struct stack_min
{
    stack<base_t> __st;
    stack<base_t> __min;
    
    void push(base_t const& v)
    {
        if (v <= min())
            __min.push(v);
        __st.push(v);
    }

    void pop()
    {
        auto const v = __st.top();
        if (v == min())
            __min.pop();
        __st.pop();
    }

    base_t top() const
    {
        return __st.top();
    }

    base_t min() const
    {
        if (__min.empty())
            return MAX_BASE;
        return __min.top();
    }

    bool empty() const
    {
        return __st.empty();
    }
};

using stack_min_t = stack_min;

int main()
{
    std::ios_base::sync_with_stdio(false);

    stack_min_t s;

    base_t v;
    while (cin >> v)
    {
        s.push(v);
        cout << s.min() << ' ' << s.top() << endl;
    }

    cout << endl;

    while (!s.empty())
    {
        cout << s.min() << ' ' << s.top() << endl;
        s.pop();
    }

    return 0;
}
