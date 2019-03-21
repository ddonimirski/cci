
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

template<class T>
bool delete_next(Node<T>* node)
{
    if (!node || node->next)
        return false;
}

template<class T>
Node<T>* delete_middle_node(Node<T>* head)
{
    Node<T>* slow = head;
    if (!slow)
        return nullptr;
    Node<T>* fast = head->next;
    if (!fast)
        return nullptr;

    auto* tmp = slow;
    while (fast)
    {
        fast = fast->next;
        tmp = slow;
        slow = slow->next;

        if (!fast)
        {
            break;
        }

        fast = fast->next;
    }

    tmp->next = slow->next;
    delete slow;

    return head;
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
