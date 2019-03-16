// 06_string_compression.cpp
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

template<class T>
struct array final
{
    int _size;
    T* _arr;

    array(int s): _size(s), _arr(new T [_size])
    {
        for (int i = 0; i < _size; ++i)
            _arr[i] = 0;
    }

    ~array()
    {
        delete [] _arr;
    }

    T& operator [](int i)
    {
        return _arr[i];
    }
};

//assumption arr has proper size
int atoi(char* arr, int val)
{
    char tmp[MAX_STR];

    int i = 0;
    while (val != 0)
    {
        auto const r = val % 10;
        tmp[i++] = r + '0';
        val /= 10;
    }

    int d = 0;
    while (i--)
    {
        arr[d++] = tmp[i];
    }

    return d;
}

void compress(char* const arr)
{
    auto const l = len(arr);

    array<char> tmp{2*l};

    tmp[0] = arr[0];
    int c = 1;
    int ci = 0;
    
    for (int i = 1; i<l ; ++i)
    {
        if (tmp[ci] != arr[i])
        {
            ci += atoi(&tmp[++ci], c);
            tmp[ci] = arr[i];
            c = 1;
        }
        else
        {
            ++c;
        }
    }

    ci += atoi(&tmp[++ci], c);
    ++ci;

    if (ci < l)
    {

        for (int i = 0; i < ci; ++i)
        {
            arr[i] = tmp[i];
        }

        arr[ci] = 0;
    }

}

int main()
{
    std::ios_base::sync_with_stdio(false);
    char arr[MAX_STR] = {0};

    cin >> arr;
    cout << arr << endl;
    compress(arr);
    cout << arr << endl;
}
