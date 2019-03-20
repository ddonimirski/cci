
#include <iostream>

using std::cout, std::cin, std::endl;

struct pr_bool
{
    bool const __bool;

    friend std::ostream& operator << (std::ostream& os, pr_bool const& v)
    {
        return os << (v.__bool?"true":"false");
    }
};

constexpr auto MAX_STR = 200;

int len(char const *const arr, int b = 0, int e = MAX_STR)
{
    while (b != e && arr[b])
    {
        ++b;
    }
    return MAX_STR - (e - b);
}

bool is_power_of_2(unsigned const& v)
{
    return !((v - 1) & (v));
}

template<class T>
struct scoup_array final
{
    size_t __size;
    T* const __ptr;
    scoup_array(int N, T const& v = 0):__size(N), __ptr(new T[N](v))
    {
    }

    ~scoup_array()
    {
        delete [] __ptr;
    }

    T& operator [](int i)
    {
        return __ptr[i];
    }

    T const& operator [](int i) const
    {
        return __ptr[i];
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    char arr[MAX_STR] = {0};

    scoup_array<int> sa{10};

    cin >> arr;
    cout << arr << endl;
}
