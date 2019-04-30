#if !defined HEAP__HPP
#define HEAP__HPP

#include <vector>
#include <stdexcept>
#include <algorithm>

static inline size_t id_left(size_t id) { return 2 * id + 1; }
static inline size_t id_right(size_t id) { return 2 * id + 2; }
static inline size_t id_parent(size_t id) { return (id - 1) / 2; }


template<class T, class COMP = std::less<T>, class CONT = std::vector<T>>
struct heap
{
    CONT __cont;
    COMP __cmp;


    explicit heap(size_t r = 7)
    {
        __cont.reserve(r);
    }

    T const& top() const
    {
        if (0 == size())
        {
            throw std::runtime_error("empty heap");
        }

        return __cont[0];
    }

    auto size() const { return __cont.size(); }
    auto empty() const { return size() == 0; }

    void exch(size_t left, size_t right)
    {
        T const tmp = __cont[left];
        __cont[left] = __cont[right];
        __cont[right] = tmp;
    }


    bool comp(size_t left, size_t right)
    {
        return __cmp(__cont[left], __cont[right]);
    }


    void swim(size_t c) //bottom-up
    {
        for (; c > 0; )
        {
            auto const p = id_parent(c);

            if (!comp(p, c))
                break;

            exch(p, c);
            c = p;
        }
    }


    void sink(size_t p) //top-down
    {
        auto const size = __cont.size();
        
        for (auto l = id_left(p); l < size; l = id_left(p))
        {
            auto const r = l + 1;
            auto const c = r < size && comp(l, r) ? r : l;

            if (!comp(p, c))
            {
                break;
            }

            exch(p, c);
            p = c;
        }
    }

    void add(T&& t)
    {
        __cont.push_back(std::forward<T>(t));
        swim(size()-1);
    }

    void add(T const& t)
    {
        add(std::move(T{t}));
    }

    T pop()
    {
        T ret = top();
        exch(0, size()-1);
        __cont.erase(std::end(__cont)-1);
        sink(0);
        return std::move(ret);
    }

    friend std::ostream& operator << (std::ostream& os, heap const& h)
    {
#if defined WITH_HEADER
        unsigned int i = 1;
        unsigned int s = 1;
        os <<"\nheap ("<< std::is_heap(h.__cont.begin(), h.__cont.end(), h.__cmp) << ")\n";
        for (auto const& v: h.__cont)
        {
            os << v << ' ';
            i++;
            if ((i >> s))
            {
                s++;
                os << '\n';
            }
        }
#else
        for (auto const& v: h.__cont)
        {
            os << v << ' ';
        }
#endif
        return os;
    }


    friend bool check_heap(heap const& h)
    {
        return std::is_heap(h.__cont.begin(), h.__cont.end(), h.__cmp);
    }

};

#endif //HEAP__HPP
