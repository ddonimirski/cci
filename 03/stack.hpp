#if !defined STACK__HPP
#define STACK__HPP

struct empty_stack_excpetion
{
};

#include "../02/list.hpp"

template<class T, template<typename> class CONT>
static inline T& get_top(CONT<T>& cont)
{
    return cont.tail();
}


template<class T>
static inline T& get_top(list<T>& cont)
{
    return cont.head();
}


template<class T, class CONT=list<T>>
class stack
{
    CONT __cont;

    public:

    stack(){}

    void push(T const& v)
    {
        __cont.add(v);
    }

    void pop()
    {
        if (__cont.empty())
            throw empty_stack_excpetion{};
        __cont.remove();
    }

    bool empty() const
    {
        return __cont.empty();
    }


    T& top()
    {
        if (__cont.empty())
            throw empty_stack_excpetion{};

        return get_top(__cont);
    }

    T const& top() const
    {
        return const_cast<stack*>(this)->top();
    }
};

#endif //STACK__HPP
