#include <iostream>
#include "stack.hpp"
#include "vector.hpp"
#include <vector>
#include "../02/list.hpp"

using std::cout, std::cerr, std::endl, std::cin;
using base_t = int;



template<class T>
struct vector_adapt:stack_policy<T, vector<T>>
{
    using cont_t = vector<T>;

    static T& top(cont_t& cont)
    {
        return cont.tail();
    }

};


template<class T>
struct list_adapt: stack_policy<T, list<T>>
{
    using cont_t = list<T>;

    static T& top(cont_t& cont)
    {
        return cont.head();
    }
};


template<class T>
struct std_vector_adapt: stack_policy<T, std::vector<T>>
{
    using cont_t = std::vector<T>;

    static T& top(cont_t& cont)
    {
        return cont[cont.size() - 1];
    }

    static void add(cont_t& cont, T const& v)
    {
        cont.push_back(v);
    }

    static void remove(cont_t& cont)
    {
        cont.pop_back();
    }

    static bool full()
    {
        return false;
    }
};



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
