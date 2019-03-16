
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


int main()
{
    std::ios_base::sync_with_stdio(false);
    char arr[MAX_STR] = {0};

    cin >> arr;
    cout << arr << endl;
}
