// g++ -std=c++17 -g -fsanitize=address 06_successorBST.cpp && echo 7 1 2 3 4 5 6 7 | ./a.out
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


node_tree_t* leftMostChild(node_tree_t* node)
{
    if (!node)
        return nullptr;

    while (node->left)
    {
        node = node->left.get();
    }

    return node;
}

node_tree_t* inorderSucc(node_tree_ptr_t const& node)
{
    if (!node) return nullptr;

    if (node->right)
    {
        return leftMostChild(node->right.get());
    }
    else
    {

        auto* q = node.get();
        auto* p = q->parent;

        if (p != nullptr && p->left.get() != q) // I've chosen 'if' insted of 'while'
        {
            q = p;
            p = q->parent;

            if (p != nullptr && p->right.get() == q)
                return nullptr;

        }

        return p;
    }
}


void pr_next(node_tree_ptr_t const& curr)
{
    if (curr)
    {
        if (auto* node = inorderSucc(curr); node)
        {
            cout << "curr node " << curr->value << " next node " << node->value << endl;
        }
        else
        {
            cout << "curr node " << curr->value << " is the last one node" << endl;
        }
    }
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
    cout << bst << endl;
    bst.pr();

    //pr_next(bst.root->left->left);
    pr_next(bst.root->left);
    pr_next(bst.root->left->right);
    pr_next(bst.root);
    pr_next(bst.root->right->left);
    pr_next(bst.root->right);
    pr_next(bst.root->right->right);
}
