#include <iostream>
#include "list.hpp"
using std::cout, std::endl, std::cin;
using base_t = int;

int main()
{
    std::ios_base::sync_with_stdio(false);

    base_t v;

    list<base_t> l;

    while (cin>>v)
    {
        l.add(v);
        cout << l.size() << endl;
    }

    while (!l.empty())
    {
        cout << l << endl;
        l.remove();
    }

    return 0;
}
