//g++ -std=c++17 02_minimalTree.cpp && echo 31 1 2 3 4 5 6 7 8 9 10 11 12 13 14
//15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31| ./a.out
#include <iostream>
#include <vector>
#include "bst_tree.hpp"


using std::cout, std::cerr, std::endl, std::cin;
using std::vector;

void pr(vector<int> const& vec)
{
    for (auto const v: vec)
    {
        cout << v << ' ';
    }
    cout << '\n';
}

void mm_Tree(bst_tree<int>& bst, vector<int> const& vec, int b, int e)
{
    if (b <= e)
    {
        auto m = (b+e)/2;
        bst.add(vec[m]);
        mm_Tree(bst, vec, m+1,e);
        mm_Tree(bst, vec, b,m-1);
    }
}

bst_tree<int> minimalTree(vector<int> const& vec)
{
    pr(vec);
    bst_tree<int> bst;

    mm_Tree(bst, vec, 0, vec.size()-1);

    return std::move(bst);
}


int main()
{

    int N;
    cin >> N;

    vector<int> vec;

    while(N--)
    {
        int v;
        cin >> v;
        vec.emplace_back(v);
    }

    auto const bst = minimalTree(vec);

    cout << "print  tree \n";
    cout << bst << endl;
    bst.pr();
}
