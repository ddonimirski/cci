// 3.5 Sort Stack: Write a program to sort a stack such that smallest items are
// on the top. You ca use an additional temporary stack, but you may not copy
// the elements into any other data structure (such as an array). The stack
// supports the following operations: push, pop, peek, empty.
// #15 - One way of sorting an array is to iterate thugh the array and insert
// each element into a new array in sorted order. Can you do this with stack?
// #32  - Imagine your secondary stack is sorted. Cay ou insert elements into it
// in sorted order? You might need some extra storage. What could you use for
// extra storage?
// #43 - 

#include <iostream>
#include "stack.hpp"
#include "stack_policy.hpp"


using std::cout, std::cerr, std::endl, std::cin;
using base_t = int;
using stack_t = stack<base_t, vector_adapt<base_t>>;

template<class CONT>
void pr(CONT const& cont)
{
    for (auto v: cont)
    {
        cout << v << ' ';
    }
    cout << endl;
}


void copy_stack(stack_t& src, stack_t& dst)
{
    while (!src.empty())
    {
        auto v = src.top();
        dst.push(v);
        src.pop();
    }
}
void copy_stack_if(stack_t& src, stack_t& dst, base_t v)
{
    while (!src.empty())
    {
        auto sv = src.top();
        if (v < sv)
            break;

        dst.push(sv);
        src.pop();
    }
}


void sort_stack(stack_t& s)
{
    stack_t out;
    stack_t tmp;

    while (!s.empty())
    {
        auto const v = s.top();
        s.pop();

        if (out.empty() || v < out.top())
        {
            out.push(v);
        }
        else
        {
            copy_stack_if(out, tmp, v);
            out.push(v);
            copy_stack(tmp, out);
        }
    }

    copy_stack(out, s);
}

int main()
{
    std::vector<base_t> arr = {1, 4, 2, 5, 6, 7, 8, 9, 4, 3, 6, 7, 8, 3, 3, 5, 7, 8, 4, 6};

    pr(arr);

    stack_t s;

    for (auto const v: arr)
    {
        s.push(v);
    }

    sort_stack(s);

    cout << s << endl; 

}
