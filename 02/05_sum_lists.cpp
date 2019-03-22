
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

using node_t = Node<int>;

node_t* sum_list(node_t* h1, node_t* h2)
{
    decltype(h1->data) rest = 0;
    node_t* sum = nullptr;

    while (h1 && h2)
    {
        auto const v1 = h1->data;
        auto const v2 = h2->data;
        rest = v1 + v2 + rest;

        sum = append(sum, rest % 10);
        rest /= 10;
        h1 = h1->next;
        h2 = h2->next;
    }

    while(h1)
    {
        rest += h1->data;
        sum = append(sum, rest % 10);
        rest /= 10;
        h1 = h1->next;
    }

    while(h2)
    {
        rest += h2->data;
        sum = append(sum, rest % 10);
        rest /= 10;
        h2 = h2->next;
    }

    while(rest)
    {
        sum = append(sum, rest % 10);
        rest /= 10;
    }

    return (sum);
}


int main()
{
    std::ios_base::sync_with_stdio(false);

    node_t* h1 = nullptr;
    node_t* h2 = nullptr;

    int v;
    while(cin >> v)
    {
        h1 = append(h1, v);
    }

    cin.clear();

    while(cin >> v)
    {
        h2 = append(h2, v);
    }


    cout << sum_list(h1, h2) << endl;

    cout << reverse(h1) << endl;
    cout << reverse(h2) << endl;

    return 0;
}
