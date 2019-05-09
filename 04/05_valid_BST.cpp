// g++ -std=c++17 -g -fsanitize=address 05_valid_BST.cpp && echo 14 1 2 3 4 5 6 7 8 9 10 11 12 13 14 | ./a.out
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


using bst_tree_t = bst_tree<int>;
using node_tree_t = node_tree<int>;
using node_tree_ptr_t = std::unique_ptr<node_tree_t>;

void mm_Tree(bst_tree_t& bst, vector<int> const& vec, int b, int e)
{
    if (b <= e)
    {
        auto m = (b+e)/2;
        bst.add(vec[m]);
        mm_Tree(bst, vec, m+1,e);
        mm_Tree(bst, vec, b,m-1);
    }
}


bst_tree_t minimalTree(vector<int> const& vec)
{
    pr(vec);
    bst_tree_t bst;

    mm_Tree(bst, vec, 0, vec.size()-1);

    return std::move(bst);
}


void copy_to_arr(node_tree_ptr_t const& root, vector<int>& vec)
{
    if (root->left) copy_to_arr(root->left, vec);
    vec.emplace_back(root->value);
    if (root->right) copy_to_arr(root->right, vec);
}


bool checkBST1(bst_tree_t const& bst)
{
    if (!bst.root) return true;

    vector<int> vec;

    copy_to_arr(bst.root, vec);

    for (int i=1; i<vec.size(); ++i)
    {
        if (vec[i-1] > vec[i])
            return false;
    }

    return true;
}

// track last elem
int const* last_printed = nullptr;

bool checkBST2_helper(node_tree_ptr_t const& node)
{
    if (!node) return true;

    if (!checkBST2_helper(node->left)) return false;

    if (last_printed && *last_printed > node->value) return false;

    last_printed = &(node->value);

    return checkBST2_helper(node->right);
}


bool checkBST2(bst_tree_t const& bst)
{
    return checkBST2_helper(bst.root);
}

// min max range

bool checkBST3_helper(node_tree_ptr_t const& node, int const* min, int const* max)
{
    if (node)
    {
        if ((min != nullptr && node->value <= *min)
                || (max != nullptr && node->value >= *max)
                || !checkBST3_helper(node->left, min, &(node->value))
                || !checkBST3_helper(node->right, &(node->value), max))
            return false;
    }

    return true;
}

bool checkBST3(bst_tree_t const& bst)
{
    return checkBST3_helper(bst.root, nullptr, nullptr);
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

    auto bst = minimalTree(vec);

    cout << "print  tree \n";
    bst.root->left->right->value = 16;
    cout << bst << endl;
    bst.pr();

    cout << checkBST1(bst) << endl;
    cout << checkBST2(bst) << endl;
    cout << checkBST3(bst) << endl;
}
