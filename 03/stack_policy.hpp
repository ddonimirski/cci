#include <vector>
#include "vector.hpp"
#include "../02/list.hpp"

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


