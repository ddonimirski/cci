#include <iostream>
#include <ios>

using std::cin, std::cout, std::endl;

constexpr int MAX_STR = 200;
constexpr int NUM_CHAR = 'z'-'a' + 1;

int get_char(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        c -= 'A';
    }

    else if (c >= 'a' && c <= 'z')
    {
        c -= 'a';
    }

    else
    {
        return -1;          
    }

    return c;
}


#if defined FIRST

int is_palindrom(char (&arr)[MAX_STR])
{
    unsigned car[NUM_CHAR] = {0};

    auto count_chars = [&]()
    {
        int s = 0;

        char c;
        for (int i = 0; i < MAX_STR && (c = arr[i]); ++i)
        {

            car[get_char(c)]++;
            s++;
        }

        return s;
    }();

    int id = -1;
    for (auto i = 0; i < NUM_CHAR; ++i)
    {
        if (car[i]%2)
        {
            if (id != -1)
                return false;
            id = i;
        }
    }

    return true;
}

#elif defined SECOND

int is_palindrom(char (&arr)[MAX_STR])
{
    int odd = 0;
    unsigned car[NUM_CHAR] = {0};

    for (int i = 0; i < MAX_STR; ++i)
    {
        auto const c = arr[i];
        if (!c) break;
        if (int id; -1 != (id = get_char(c)))
        {
            car[id]++;
            if (car[id]%2)
            {
                odd++;
            }

            else
            {
                odd--;
            }
        }
    }

    return odd <= 1;
}


#else

int is_palindrom(char (&arr)[MAX_STR])
{
    unsigned car = 0;

    for (int i = 0; i < MAX_STR; ++i)
    {
        auto const c = arr[i];
        if (!c) break;

        if (int id; -1 != (id = get_char(c)))
        {
            unsigned mask = 1 << id;

            if (mask & car)
            {
                car &= ~mask;
            }
            else
            {
                car |= mask;
            }
        }
    }

    return car == 0 || ((car - 1) & car) == 0;
}

#endif


int main()
{
    std::ios_base::sync_with_stdio(false);
    char arr[MAX_STR] = {0};
    cin >> arr;

    cout << (is_palindrom(arr)?"True": "False") << endl;

}
