#if !defined STACK__HPP
#define STACK__HPP
#include <iostream>

struct empty_stack_excpetion
{
};

struct full_stack_exception
{
};


template<class T, class CONT>
struct stack_policy
{
    using cont_t = CONT;

    static void add(cont_t& cont, T const& v)
    {
        cont.add(v);
    }


    static void remove(cont_t& cont)
    {
        cont.remove();
    }


    static T& top(cont_t& cont)
    {
        return cont.top();
    }


    static bool empty(cont_t const & cont)
    {
        return cont.empty();
    }


    static bool full(cont_t const& cont)
    {
        return cont.full();
    }

    static size_t size(cont_t const& cont)
    {
        return cont.size();
    }
};


template<class T, class ADAPT>
class stack
{
    typename ADAPT::cont_t __cont;

    public:

    stack(){}

    void push(T const& v)
    {
        ADAPT::add(__cont, v);
    }

    void pop()
    {
        if_empty_throw();
        ADAPT::remove(__cont);
    }

    bool empty() const
    {
        return ADAPT::empty(__cont);
    }

    void if_empty_throw() const
    {
        if (empty())
            throw empty_stack_excpetion{};
    }

    bool full() const
    {
        return ADAPT::full(__cont);
    }

    void if_full_throw() const
    {
        if(full())
            throw full_stack_exception{};
    }


    T& top()
    {
        if_empty_throw();
        return ADAPT::top(__cont);
    }

    T const& top() const
    {
        return ADAPT::top(__cont);
    }

    size_t size() const
    {
        return ADAPT::size(__cont);
    }

    friend std::ostream& operator << (std::ostream& os, stack const& s)
    {
        if (!s.empty())
            for (auto const v: s.__cont)
            {
                os << v << ' ';
            }
        else
            os << "empty stack";
        return os;
    }
};

#endif //STACK__HPP
