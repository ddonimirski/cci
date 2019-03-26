//g++ std=c++17 -Wall -Wextra -pedantic -pipe  -O2 % && echo 1 2 3 4 + 5 6 7 8 9 10 | ./a.out/ 
// 5 [head of loop]
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
    cout << " add " << v <<endl;

    new_head->next = head;

    return new_head;
}

template<class T>
std::ostream& operator<< (std::ostream& os, Node<T> const* head)
{
    int i = 0;
    while(head)
    {
        os << head->data << ' ';
        head = head->next;
        if (++i > 20)
            break;
    }
    return os;
}


using base_t = int;
using node_t = Node<base_t>;

node_t* loop_detection(node_t* head)
{
    auto* slow = head;
    auto* fast = head;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) // loop detected
        {
            break;
        }
    }


    if (!fast || !fast->next) // fast could hit the end
        return nullptr;


    //Move slow to head. Keep fast at meeting point, each are k steps from the
    //loop start. If they move at the same pace, so they must meet at loop start
    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    //both are the same
    return fast;
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
    node_t* tail = nullptr;

    base_t v;

    if (cin>>v)
    {
        tail = h1 = append(h1, v);
    }

    else
    {
        return 0;
    }


    while (cin >> v)
    {
        h1 = append(h1, v);
    }

    cin.clear();

    if (cin >> v)
    {
        h1 = append(h1, v);
        tail->next = h1;
    }

    while (cin >> v)
    {
        h1 = append(h1, v);
    }

    cout << h1 << endl;

    auto* node = loop_detection(h1); 
    cout << "loop was" << pr_bool{!!node} << " detected\n";
    if (node)
    {
        cout << node->data << endl;
    }

    return 0;
}
