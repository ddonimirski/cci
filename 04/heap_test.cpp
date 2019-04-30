#include <iostream>
#include "heap.hpp"
#include <functional>
#include <algorithm>


using std::cout, std::cerr, std::endl;

template<class C>
void pr(C const& c)
{
    for (auto const& v: c)
        cout << v << ' ';
    cout << endl;
}


int main()
{

    //std::ios::sync_with_stdio(false);
    std::vector data{ 1, 2 ,3 ,4 , 5 ,6, 7 ,8, 9, 10 };
    heap<int, std::greater<int>> h(data.size());

    cout << "test heap in progress...";
    cout.flush();

    do
    {
#if defined PRINT_PERMUTATION
        pr(data);
#endif
        for (auto const v: data)
        {
            h.add(v);
            if (!check_heap(h))
            {
                cout << "failed" << endl;
                cout << h << endl;
                return 1;
            }
        }

        while (!h.empty())
        {
            h.pop();
            if (!check_heap(h))
            {
                cout << "failed" << endl;
                cout << h << endl;
                return 1;
            }
        }

    } while (std::next_permutation(data.begin(), data.end()));


    cout << "success" << endl;
    return 0;
}
