
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
void erase_all(Node<T>* head)
{
    while (head)
    {
        auto* tmp = head;
        head = head->next;
        delete tmp;
    }
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
Node<T>* remove_dup(Node<T>* head)
{
    if (!head)
        return head;

    auto* ret = head;

    int hh[10] = {0}; // in other case use hash_table

    auto* cur = head;

    while (head)
    {
        if (hh[head->data])
        {
            cur->next = head->next;
            delete head;
            head = cur->next;
        }
        else
        {
            hh[head->data]++;
            cur = head;
            head = head->next;
        }
    }

    return ret;
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

    remove_dup(head);

    cout << head << endl;

}
