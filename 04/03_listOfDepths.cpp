//g++ -std=c++17 -Ofast 03_listOfDepths.cpp && echo 14 1 2 3 4 5 6 7 8 9 10 11 12 13 14 | ./a.out
#include <iostream>
#include <vector>
#include <list>
#include <memory>
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


void createLevelLinkedList(std::unique_ptr<node_tree_t> const& root, levelLinkedList_t& lists, int level)
{
    if (!root) return; // base case :P


    if (lists.size() == level) // Level not contained in list
    {
        linkList_t list;
        list.push_back(root.get());
        lists.emplace_back(std::move(list));
    }
    else
    {
        lists[level].push_back(root.get());
    }

    createLevelLinkedList(root->left, lists, level+1);
    createLevelLinkedList(root->right, lists, level+1);
}


levelLinkedList_t createLevelLinkedList(std::unique_ptr<node_tree_t> const& root)
{
    levelLinkedList_t result;

    linkList_t current;

    if (root)
    {
        current.push_back(root.get());
    }

    while (current.size()>0)
    {
        result.push_back(current);
        linkList_t parents = std::move(current);
        current = std::move(linkList_t());

        for (auto& parent: parents)
        {
            if (parent->left)
            {
                current.push_back(parent->left.get());
            }
            if (parent->right)
            {
                current.push_back(parent->right.get());
            }
        }
    }

    return std::move(result);
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

    levelLinkedList_t lists;
    createLevelLinkedList(bst.root, lists, 0);
    pr_list(lists);
    pr_list(createLevelLinkedList(bst.root));
}
