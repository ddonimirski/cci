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
Node<T>* erase(Node<T>* head)
{
    if (!head || !(head->next))
        return nullptr;

    auto* new_head = head->next;
    delete head;

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
Node<T>* runner(Node<T>* head)
{
    auto* __slow = head;
    auto* __fast = head;

    while(__fast)
    {
        __slow = __slow->next;
        __fast = __fast->next->next;
    }

    __fast = head->next;
    head->next = nullptr;

    auto* tmp = __slow;
    __slow = tmp->next;
    tmp->next = head;
    head = tmp;

    while(__slow)
    {
        tmp = __fast;
        __fast = tmp->next;
        tmp->next = head;
        head = tmp;

        tmp = __slow;
        __slow = tmp->next;
        tmp->next = head;
        head = tmp;
    }

    return head;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int v;

    Node<int>* head = nullptr;

    while(cin >> v)
    {
        head = append(head, v);
    }

    head = runner(head);

    cout << head << endl;

}
