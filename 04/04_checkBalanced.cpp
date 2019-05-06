// g++ -std=c++17  04_checkBalanced.cpp && echo 14 1 2 3 4 5 6 7 8 9 10 11 12 13 14 | ./a.out
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <limits>
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


using bst_tree_t = bst_tree<int>;
using node_tree_t = node_tree<int>;
using linkList_t = std::list<node_tree_t*>;
using levelLinkedList_t  = std::vector<linkList_t>;

void pr_list(levelLinkedList_t const& vec)
{
    for (auto& lst: vec)
    {
        for (auto& n: lst)
        {
            cout << n->value << ' ';
        }
        cout << endl;
    }

    cout << endl;
}


int getHeight(std::unique_ptr<node_tree_t> const& root)
{
    if (root)
        return std::max(getHeight(root->left), getHeight(root->right))+1;
    return -1;
}


bool isBalanced(std::unique_ptr<node_tree_t> const& root)
{
    if (!root) return true;

    int heightDiff = getHeight(root->left) - getHeight(root->right);
    if (std::abs(heightDiff)>1)
        return false;
    else
        return isBalanced(root->left) && isBalanced(root->right);
}


int checkHeight(std::unique_ptr<node_tree_t> const& root)
{
    if (!root) return -1;

    int const leftHeight = checkHeight(root->left);
    if (leftHeight == std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();

    int const rightHeight = checkHeight(root->right);
    if (rightHeight == std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();

    int const heightDiff = leftHeight - rightHeight;
    if (std::abs(heightDiff)>1)
        return std::numeric_limits<int>::min();
    else
        return std::max(leftHeight, rightHeight) + 1;

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

    cout << isBalanced(bst.root) << endl;
    cout << checkHeight(bst.root) << endl;
}
