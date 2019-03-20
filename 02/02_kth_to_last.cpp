//g++ -std=c++17 -Wall -Wextra -pedantic -pipe -O2 [-DBEGIN] [-DITER]
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
        os << head->data;
        head = head->next;
    }
    return os;
}

#if defined BEGIN

#if defined ITER
template<class T>
Node<T>* get_kth_to_last(Node<T>* head, int k)
{
    if (head)
    {
        Node<T>* end = head;

        while (k--)
        {
            if (!end)
                return nullptr;

            end = end->next;
        }

        while(end)
        {
            end = end->next;
            head = head->next;
        }
    }

    return head;
}
#else
template<class T>
Node<T>* get_kth_to_last(Node<T>* head, int& k)
{
    if (head)
    {
        Node<T>* const ret = get_kth_to_last(head->next, k);
        --k;
        if (k < 0 && ret)
        {
            return ret;
        }
        else if (k > 0)
        {
            return nullptr;
        }
    }

    return head;
}
#endif

#else

#if defined ITER
template<class T>
Node<T>* get_kth_to_last(Node<T>* head, int k)
{
    if (head)
    {
        for (int i = 1; i < k; ++i)
        {
            head = head->next;
        }
    }

    return head;
}
#else
template<class T>
Node<T>* get_kth_to_last(Node<T>* head, int k)
{
    if (head && k>1)
    {
        return get_kth_to_last(head->next, k-1);
    }

    return head;
}
#endif

#endif

int main()
{
    std::ios_base::sync_with_stdio(false);
    int K;
    cin >> K;

    if (K <= 0)
    {
        cout << "k - must be greater then zero\n";
        return 0;
    }

    int v;

    Node<int>* head = nullptr;

    while(cin >> v)
    {
        head = append(head, v);
    }

    cout << K << ' ' << head << endl;
    if (auto* node = get_kth_to_last(head, K))
    {
        cout << node->data << endl;
    }
    else
    {
        cout << "not found" << endl;
    }
    return 0;
}
