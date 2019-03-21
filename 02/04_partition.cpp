// g++ -std=c++17 -Wall -Wextra -pedantic -pipe -O2 04_partition.cpp 
// && echo 1 
#include <iostream>

using std::cout, std::cin, std::endl;

struct pr_bool_msg
{
    bool const _val;
    char const *const _true;
    char const *const _false;

    pr_bool_msg(bool v, char const* t = "true", char const* f = "false")
        :_val(v), _true(t), _false(f)
        {}

    friend std::ostream& operator << (std::ostream& os, pr_bool_msg const& v)
    {
        return os << (v._val ? v._true, v._false);
    }
};

template<class T>
struct Node
{
    Node* next;
    T data;

    Node(T const& v): next(nullptr), data(v) {}

};

template<class T>
Node<T>* append_new(Node<T>* head, T const& v)
{
    auto* new_head = new Node<T>{v};

    new_head->next = head;

    return new_head;
}

template<class T>
{
}


int main()
{
    std::ios_base::sync_with_stdio(false);

    Node<int>* head = nullptr;

    int v;
    while(cin >> v)
    {
        head = append(head, v);
    }
    cout << head << endl;

    if ((head = delete_middle_node(head)))
    {
        cout << head << endl;
    }
    else
    {
        cout << "empty list\n";
    }

    return 0;
}
