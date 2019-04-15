// 3.4 Queue via Stacks: Implement a queue_via_stack which implements a queue
// using stacks
// #98 - The major difference between a queue and a stack is  the order of
// elements. A queue remove the oldest item and stack removes the newst item.
// How could you remove the oldest item from a stack if you only had access to
// the newst item?
// #114 - We can remove the oldest item orm a stack by repeatedly removing the
// newset item (inserting those into the temporary stack) until we get down to
// one element. Then, after we've retrived the newest item, putting all the
// elements back. The issue with this is that doing several pops in a row will
// require O(N) work each time. Can we optimize for scenaios where we might do
// several pops in a row?

#include <iostream>
#include "stack.hpp"
#include "stack_policy.hpp"


using std::cout, std::cerr, std::endl, std::cin;
using base_t = int;
using stack_t = stack<base_t, std_vector_adapt<base_t>>;


struct queue_via_stack
{
    stack_t __in;
    stack_t __out;

#if 0
    int size()
    {
        //TODO: implement size interface
        return __in.size() + __out.size();
    }
#endif

    bool empty() const
    {
        return __in.empty() && __out.empty();
    }

    void add(base_t const& value)
    {
        __in.push(value);
    }

    base_t pop()
    {
        if (__out.empty())
        {
            while(!__in.empty())
            {
                __out.push(__in.top());
                __in.pop();
            }
        }

        __out.if_empty_throw();
        auto res =  __out.top();
        __out.pop();
        return res;
    }
};


int main() 
{
    std::vector<base_t> input = { 1, 2, 3, 4, 5, 6, 7, 8, 9};

    queue_via_stack queue;

    auto const v_size = input.size();
    auto i = 0u;
    for (; i < v_size/2; i++ )
    {
       queue.add(input[i]); 
    }

    for (auto i = 0u; i < v_size/4; i++ )
    {
        cout << queue.pop() << endl;
    }

    for (; i < v_size; i++ )
    {
       queue.add(input[i]); 
    }

    while (!queue.empty())
    {
        cout << queue.pop() << endl;
    }
}
