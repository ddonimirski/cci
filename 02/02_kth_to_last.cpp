#include <iostream>

using std::cout, std::cin, std::endl;

struct pr_bool
{
    bool const __bool;

    friend std::ostream& operator << (std::ostream& os, pr_bool const& v)
    {
        return os << (v.__bool?"true":"false");
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

template<class T>
Node<T>* get_kth_to_last(Node<T>* head, int& k)
{
    if (!head)
    {
        return head;
    }

    auto* ret = get_kth_to_last(head->next, k);
    --k;
    if (!k)
    {
        return ret;
    }
    return head;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int K;
    cin >> K;

    int v;

    Node<int>* head = nullptr;

    while(cin >> v)
    {
        head = append(head, v);
    }

    head = get_kth_to_last(head, K);

    cout << head << endl;

}
