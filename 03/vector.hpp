// simple vector for copible 
#if !defined VECTOR_HPP
#define VECTOR_HPP

struct empty_vector_exception
{
};

template<class T>
class vector
{
    T* __arr;
    size_t __size;
    size_t __capasicty;

    static constexpr size_t DEFAULT_CPACITY = 4;

    void __inc()
    {
        auto const s_tmp = __capasicty * 2;
        T* tmp =  new T[s_tmp];

        // copy current
        for (auto i = 0ull; i < __capasicty; ++i)
        {
            tmp[i] = __arr[i];
        }

        delete [] __arr;
        __arr = tmp;
        __capasicty = s_tmp;
    }

    public:

    vector():__arr(new T[DEFAULT_CPACITY]), __size(0),
            __capasicty(DEFAULT_CPACITY) { }

    ~vector() { delete [] __arr; }

    void add(T const& v)
    {
        if (__capasicty == __size)
        {
            __inc();
        }

        __arr[__size++] = v;

    }

    void remove()
    {
       --__size;
    }

    bool empty() const
    {
        return __size == 0;
    }

    bool full() const
    {
        return false;
    }

    T& head()
    {
        if (empty())
            throw empty_vector_exception{};
        return __arr[0];
    }

    T& tail()
    {
        if (empty())
            throw empty_vector_exception{};
        return __arr[__size - 1];
    }

    T& operator[](int id)
    {
        return __arr[id];
    }
};

#endif //VECTOR_HPP
