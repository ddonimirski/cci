#include <iostream>
#include "binary_tree.hpp"

using std::cout, std::cin, std::endl, std::cerr;


int main() 
{
    std::ios::sync_with_stdio(false);

    binary_tree t;

    t.root.reset(new node{3});
    t.root->add(1);
    t.root->add(4);

    cout << t << endl;
}
