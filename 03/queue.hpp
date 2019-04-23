#if !defined QUEUE__HPP
#define QUEUE__HPP
#include <iostream>


struct empty_queue_excpetion
{
};

struct full_queue_exception
{
};


template<class T, class CONT>
struct queue_policy
{
    using cont_t = CONT;

    static void enqueue(cont_t& cont, T const& v)
    {
        cont.push_back(v);
    }

    static void dequeue(cont_t& cont)
    {
        cont.pop_front();
    }

    static T& front(cont_t& cont)
    {
        return cont.front();
    }

    static T& back(cont_t& cont)
    {
        return cont.back();
    }

    static size_t size(cont_t const& cont) 
    {
        return cont.size();
    }

    static bool empty(cont_t const& cont)
    {
        return cont.empty();
    }
};


template<class T, class ADAPT>
struct queue
{
    typename ADAPT::cont_t __cont;

    void enqueue(T const& v)
    {
        ADAPT::enqueue(__cont, v);
    }

    void dequeue()
    {
        if_empty_throw();
        ADAPT::dequeue(__cont);
    }


    void if_empty_throw() const
    {
        if (empty())
            throw empty_queue_excpetion{};
    }

    bool empty() const
    {
        return ADAPT::empty(__cont);
    }

    size_t size()
    {
        return size(__cont);
    }

    T& front()
    {
        return ADAPT::front(__cont);
    }

    T& back()
    {
        return ADAPT::back(__cont);
    }

    friend std::ostream& operator << (std::ostream& os, queue const& s)
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

#endif // QUEUE__HPP
