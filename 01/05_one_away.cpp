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


#if defined FIRST
bool is_one_edit(char const *const arrL, int ll, char const * const arrR)
{
    bool found = false;

    for (auto i = 0; i < ll; ++i)
    {
        if (arrL[i] != arrR[i])
        {
            if (found)
                return false;
            found = true;
        }
    }

    return true;
}


bool is_one_insert(char const *const arrL, int ll, char const * const arrR, int lr)
{
    int l = 0, r = 0;

    while (l < ll && r < lr)
    {
        if (arrL[l] != arrR[r])
        {
            if (l != r)
            {
                return false;
            }
            else
            {
                ++r;
            }
        }
        else
        {
            ++l, ++r;
        }
    }

    return true;
}
#elif defined SECOND
bool is_one_edit(char const *const arrL, char const * const arrR)
{
    bool found = false;
    for (unsigned i = 0u; arrL[i]; ++i)
    {
        if (arrL[i] != arrR[i])
        {
            if (found)
                return false;

            found = true;
        }
    }

    return true;
}


bool is_one_insert(char const *const arrL, char const * const arrR)
{
    unsigned l = 0, r = 0;

    while (arrL[l] && arrR[r])
    {
        if (arrL[l] != arrR[r])
        {
            if (l != r)
                return false;
            ++r; // assumption len(arrL) + 1 == len(arrR)
        }
        else
        {
            ++r, ++l;
        }
    }

    return true;
}
#endif


bool is_one_away(char const *const arrL, char const *const arrR)
{
    auto const ll = len(arrL);
    auto const lr = len(arrR);

#if defined FIRST
    if (ll == lr)
        return is_one_edit(arrL, ll, arrR);
    else if (ll + 1 == lr)
        return is_one_insert(arrL, ll, arrR, lr);
    else if (ll - 1 == lr)
        return is_one_insert(arrR, lr, arrL, ll);
#elif defined SECOND
    if (ll == lr)
        return is_one_edit(arrL, arrR);
    else if (ll + 1 == lr)
        return is_one_insert(arrL, arrR);
    else if (ll - 1 == lr)
        return is_one_insert(arrR, arrL);
#else
#define abs(v) ((v) >  0 ? (v) : -(v))
    if (abs(ll - lr) > 1)
        return false;

    char const* const arrl = ll > lr ? arrR : arrL;
    char const* const arrr = ll > lr ? arrL : arrR;

    unsigned l = 0, r = 0;
    bool found = false;
    while (arrl[l] && arrr[r])
    {
        if (arrl[l] != arrr[r])
        {
            if (found)
                return false;

            found = true;

            if (ll == lr)
            {
                ++l;
            }
        }
        else
        {
            ++l;
        }
        ++r;
    }

#endif

    return false;
}


int main()
{
    std::ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while (T--)
    {
        char arrL[MAX_STR] = {0};
        char arrR[MAX_STR] = {0};

        cin >> arrL;
        cin >> arrR;

        cout << arrL << ", " << arrR << " -> " << pr_bool{is_one_away(arrL, arrR)} << endl;
    }
}
