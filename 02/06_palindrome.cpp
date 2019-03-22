
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

using node_t = Node<char>;


struct pr_bool
{
    bool const __bool;

    friend std::ostream& operator << (std::ostream& os, pr_bool const& v)
    {
        return os << (v.__bool?"true":"false");
    }
};


#if defined REVERSE
bool is_palindrome(node_t* head)
{
    node_t* keep_head = head;
    node_t* rev = nullptr;
    
    while (head)
    {
        rev = append(rev, head->data);
        head = head->next;
    }

    while (keep_head && rev)
    {
        if (keep_head->data != rev->data)
        {
            return false;
        }

        keep_head = keep_head->next;
        rev = rev->next;
    }

    return true;
}
#elif defined RECURSIVE

struct ret
{
    node_t* node;
    bool result;
};

ret* rec(node_t* head, node_t* fast)
{
   if (fast) 
   {
       if (fast->next)
       {
           auto* ret = rec(head->next, fast->next->next);
           ret->result = ret->result && ret->node->data == head->data;
           ret->node = ret->node->next;
           return ret;
       }

       return new ret{head->next, true};
   }

   return new ret{head, true};
}

bool is_palindrome(node_t* head)
{
    ret* r = rec(head, head);
    auto const tmp_r = r->result;
    delete r;
    return tmp_r;
}

#elif defined STACK

bool is_palindrome(node_t* head)
{
#error NOT IMPLEMNTED
    return false;
}

#else
bool is_palindrome(node_t* head)
{
// copy list if you want keep it save :P
//
    if (!head)
        return false;

    auto* slow = head;
    auto* fast = head;
    node_t* rev = nullptr;

    while (fast)
    {
        auto* const tmp = slow;
        slow = slow->next;
        if (!(fast = fast->next))
        {
            break;
        }
        rev = append_nodes(rev, tmp);
        fast = fast->next;
    }

    while (slow)
    {
        if (rev->data != slow->data)
        {
            return false;
        }
        rev = rev->next;
        slow = slow->next;
    }

    return true;
}
#endif

int main()
{
    std::ios_base::sync_with_stdio(false);

    node_t* h1 = nullptr;

    char v;
    while(cin >> v)
    {
        h1 = append(h1, v);
    }


    cout << h1 << endl;
    cout << pr_bool{is_palindrome(h1)} << endl;

    return 0;
}
