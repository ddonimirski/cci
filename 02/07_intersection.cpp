//g++ std=c++17 -Wall -Wextra -pedantic -pipe  -O2 % && echo 1 2 3 4 + 5 6 7 8 9 10 | ./a.out/ 
#include <iostream>

using std::cout, std::cin, std::endl;

template<class T>
struct Node
{
    Node* next;
    T data;

    Node(T const& v): next(nullptr), data(v) {}

};

template<class T>
Node<T>* append(Node<T>* head, T const& v)
{
    auto* new_head = new Node<T>{v};

    new_head->next = head;

    return new_head;
}

template<class T>
std::ostream& operator<< (std::ostream& os, Node<T> const* head)
{
    while(head)
    {
        os << head->data << ' ';
        head = head->next;
    }
    return os;
}


template<class T>
Node<T>* append_nodes(Node<T>* head, Node<T>* next)
{
    if (!next)
        return head;

    next->next = head;
    return next;
}

template<class T>
size_t len(Node<T>* head)
{
    size_t len = 0;
    while (head)
    {
        head = head->next;
        ++len;
    }
    return len;
}

template<class T>
Node<T>* reverse(Node<T>* head)
{
    Node<T>* ret = nullptr;

    while(head)
    {
        auto* tmp = head;
        head = head->next;
        ret = append_nodes(ret, tmp);
    }

    return ret;
}

using base_t = int;
using node_t = Node<base_t>;

node_t* find_intersection(node_t* h1, node_t* h2)
{
    size_t const l1 = len(h1);
    size_t const l2 = len(h2);

    auto* node = (l1 > l2) ? h1 : h2;
    auto* low = (l1 > l2) ? h2 : h1;

    // make they lenght equal 
    for (auto d = (l1 > l2) ? (l1 - l2) : (l2 - l1); d && node; --d)
    {
        node = node->next;
    }

    while (node &&  low)
    {
        if (node == low)
            return node;
        node = node->next;
        low = low->next;
    }

    return nullptr;
}


struct pr_bool
{
    bool const __bool;

    friend std::ostream& operator << (std::ostream& os, pr_bool const& v)
    {
        return os << (v.__bool?"":" not");
    }
};



int main()
{
    std::ios_base::sync_with_stdio(false);

    node_t* h1 = nullptr;

    base_t v;
    while (cin >> v)
    {
        h1 = append(h1, v);
    }

    cin.clear();

    node_t* h2 = h1;

    while (cin >> v)
    {
        h1 = append(h1, v);

        if (!(cin>>v))
            break;

        h2 = append(h2, v);
    }

    cin.clear();

    while (cin>>v)
    {
        h2 = append(h2, v);
    }

    cout << h1 << endl;
    cout << h2 << endl;

    auto* node = find_intersection(h1, h2); 
    cout << "interserction was" << pr_bool{!!node} << " found\n";
    if (node)
    {
        cout << node << endl;
    }

    return 0;
}
