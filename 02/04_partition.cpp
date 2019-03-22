// g++ -std=c++17 -Wall -Wextra -pedantic -pipe -O2 04_partition.cpp 
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
Node<T>* partition(Node<T>* head, T const& v)
{
    Node<T>* gt = nullptr;
    Node<T>* g = nullptr;
    Node<T>* lt = nullptr;
    Node<T>* l = nullptr;

    while (head)
    {
        Node<T>* tmp = head;
        head = head->next;
        if (tmp->data >= v)
        {
            g = append_nodes(g, tmp);
            if (!gt)
            {
                gt = g;
            }
        }
        else
        {
            l = append_nodes(l, tmp);
            if (!lt)
            {
                lt = l;
            }
        }
    }

    if (gt)
    {
        gt->next = l;
        return g;
    }
    else if (lt)
    {
        lt->next = g;
        return l;
    }

    return nullptr;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    Node<int>* head = nullptr;

    int p;
    cin >> p;

    int v;
    while(cin >> v)
    {
        head = append(head, v);
    }
    cout << head << endl;

    if ((head = partition(head, p)))
    {
        cout << head << endl;
    }
    else
    {
        cout << "empty list\n";
    }

    return 0;
}
