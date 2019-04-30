#if !defined BINARY_TREE__HPP
#define BINARY_TREE__HPP

#include <iostream>
#include <memory>


template<class N = int>
struct node
{
    N value;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;

    node(N v): value(v) {}

    std::unique_ptr<node> add(N v)
    {
        if (value < v)
        {
            auto ret = std::move(right);
            right.reset(new node{v});
            return ret;
        }
        else
        {
            auto ret = std::move(left);
            left.reset(new node{v});
            return ret;
        }
    }

    friend std::ostream& operator << (std::ostream& os, node const& n)
    {
        if (n.left.get() != nullptr) os << *n.left;
        os << n.value << ' ';
        if (n.right.get() != nullptr) os << *n.right;
        return os;
    }
};


template<class N=int>
struct binary_tree
{
    std::unique_ptr<node<N>> root;


    friend std::ostream& operator << (std::ostream& os, binary_tree const& t)
    {
        if (t.root.get() != nullptr)
            return os << *t.root;

        return os << "empty tree";
    } 
};

#endif //BINARY_TREE__HPP

