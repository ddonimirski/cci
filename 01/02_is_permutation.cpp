#include <iostream>

using std::cin, std::cout, std::endl;

constexpr int MAX_STR = 200;
constexpr int NUM_CHAR = 256;

int count(char (&arr)[MAX_STR], unsigned (&v)[NUM_CHAR])
{
    int ret = 0;
    for (auto const c: arr)
    {
        if (c)
        {
            v[c]++;
        }

        else
            break;
    }
}

#if defined FIRST
bool is_same(unsigned (&v1)[NUM_CHAR], unsigned (&v2)[NUM_CHAR])
{
    for (int i = 0; i < NUM_CHAR; ++i)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
} 
#else
bool same_lenght(char (&arr1)[MAX_STR], char(&arr2)[MAX_STR])
{
    for (int i = 0; i < MAX_STR; ++i)
    {
        if (!arr1[i] || !arr2[i])
        {
            return arr1[i] == arr2[i];
        }
    }

    return true;
}

bool is_same(char (&arr)[NUM_CHAR], unsigned (&v)[NUM_CHAR])
{
    for (auto const c: arr)
    {
        v[c]--;
        if (
    }
    return true;
} 
#endif

int main()
{
    std::ios_base::sync_with_stdio(false);

    char arr[MAX_STR] = {0};
    unsigned v1[NUM_CHAR] = {0};
#if defined FIRST
    unsigned v2[NUM_CHAR] = {0};
#endif


    cin >> arr;
    count(arr, v1);

    cin >> arr;
#if defined FIRST
    count(arr, v1);
#endif

#if defined FIRST
    cout << (is_same(v1,v2)?"True":"False") << endl;
#else


    cout << (is_same(arr,v1)?"True":"False") << endl;
#endif

    return 0;
}

