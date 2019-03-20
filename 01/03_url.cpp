#include <iostream>

using std::cin, std::cout, std::endl;

constexpr int MAX_STR = 200;


static inline int count(char const* arr, int& sc)
{
    int s = 0;
    sc = 0;

    while(*arr)
    {
        ++s;
        if (*arr++ == ' ')
            ++sc;
    }

    return s;
}

void space_url(char (&arr)[MAX_STR])
{
    int s_count;
    auto const s_len = count(arr, s_count);

    if (s_count == 0)
        return;

    auto dest = s_len + (2) * s_count; // (2 == len("%20") - 1) * s_count
    arr[dest] = 0; // terminate

    for (auto i = s_len-1; i >= 0 && s_count; --i)
    {
        if (arr[i] == ' ')
        {
            arr[--dest] = '0';
            arr[--dest] = '2';
            arr[--dest] = '%';
            --s_count;
        }

        else
        {
            arr[--dest] = arr[i];
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    char arr[MAX_STR] = {0};

    if(cin.getline(arr, MAX_STR))
    {
        space_url(arr);
        cout << arr << endl;
    }
}
