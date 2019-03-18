
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

void rotate(char* const arr)
{
    auto const _len = len(arr);

    auto b = 0, e = _len-1;

    while(b < e)
    {
        char const tmp = arr[b];
        arr[b++] = arr[e];
        arr[e--] = tmp;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    char arr[MAX_STR] = {0};

    cin >> arr;
    rotate(arr);
    cout << arr << endl;
}
