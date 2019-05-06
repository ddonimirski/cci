#if !defined BST_TREE__HPP
#define BST_TREE__HPP

#include <memory>
#include <iostream>
#include <vector>
#include <string_view>

static std::string_view LEFT("left");
static std::string_view RIGHT("right");
static std::string_view SPACE("\t ");


template<class T>
struct node_tree
{
    using type_t = T;

    T value;
    std::unique_ptr<node_tree> left; 
    std::unique_ptr<node_tree> right;

    node_tree()
        : value{T{}}
    { }

    node_tree(node_tree&& n)
        : value{n.value},
            left{std::move(n.left)},
            right{std::move(n.right)}
    { }

    node_tree(node_tree const& n) = default;


    explicit node_tree(T&& v)
        : value{v}
    { }

    explicit node_tree(T const& v)
        : value{v}
    { }

    friend std::ostream& operator<<(std::ostream& os, node_tree const& n)
    {
        if (n.left) os << *n.left;
        os << n.value << ' ';
        if (n.right) os << *n.right;
        return os;
    }


    void pr() const
    {
        static std::vector<std::string_view> pr_deep;

        auto pr_v = [&]()
        {
            for (auto v: pr_deep)
                std::cout << v ;
        };

        if (left)
        {
            pr_deep.push_back(SPACE);
            left->pr();
            pr_deep.pop_back();
        }
        pr_v();
        std::cout << value << "\n";
        if (right)
        {
            pr_deep.push_back(SPACE);
            right->pr();
            pr_deep.pop_back();
        }
    }
};


template<class T = int>
struct bst_tree
{
    using node_tree_t = node_tree<T>;
    using node_tree_ptr_t = std::unique_ptr<node_tree_t>;
    node_tree_ptr_t root;

    bst_tree() { }

    bst_tree(bst_tree&& bst)
        : root{std::move(bst.root)}
    { }

    bst_tree(bst_tree const& ) = delete;

    void add(T const& v)
    {
        if (!root)
            root.reset(new node_tree_t{v});
        else
            add(new node_tree_t{v}, root);
    }

    void add(T&& v)
    {
        if (!root)
            root.reset(new node_tree_t{std::forward<node_tree_t>(v)});
        else
            add(new node_tree_t{std::forward<node_tree_t>(v)}, root);
    }

    void add(node_tree_t* v, node_tree_ptr_t& p)
    {
        if (auto& n = (v->value < p->value)? p->left: p->right; n)
        {
            add(v, n);
        }
        else
        {
            n.reset(v);
        }
    }

    void pr() const
    {
        if (root)
        {
            //std::cout << "root (" << root.value << ")";
            root->pr();
        }
        else
        {
            std::cout << "empty tree\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, bst_tree const&  bst)
    {
        if (bst.root)
        {
            os << *bst.root;
        }
        else
        {
            os << "empty bst_tree";
        }

        return os;
    }
};

#endif //BST_TREE__HPP
