#if !defined LIST_HPP
#define LIST_HPP

#include <stdexcept>

template<class T>
struct Node
{
    Node* next;
    T data;

    Node(T const& v): next(nullptr), data(v) {}

};


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
Node<T>* append(Node<T>* head, T const& v)
{
    auto* new_head = new Node<T>{v};

    new_head->next = head;

    return new_head;
}

template<class T>
Node<T>* erase(Node<T>* head)
{
    if (head)
    {
        auto* tmp = head;
        head = head->next;
        delete tmp;
    }

    return head;
}

template<class T>
Node<T>* tail_append(Node<T>* head, T const& v)
{
    auto tmp = new Node<T>(v);
    if (!head)
    {
        return tmp;
    }

    auto* step = head;
    while (step->next)
    {
        step = step->next;
    }
    step->next = tmp;

    return head;
}


template<class T>
Node<T>* tail_erase(Node<T>* head)
{
    if (head)
    {
        if (head->next)
        {
            auto* step = head;
            while (step->next->next)
            {
                step = step->next;
            }
            delete step->next;
            step->next = nullptr;
            return head;
        }
        delete head;
    }

    return nullptr;
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
size_t len(Node<T>* head)
{
    size_t len = 0;
    while (head)
    {
        head = head->next;
        ++len;
    }
    return len;
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

struct empty_list_exception
{
};


template<class T>
class list
{
    Node<T>* __head = nullptr;
    size_t __size = 0;

    public:

    void add(T const& value)
    {
        __head = append(__head, value);
        ++__size;
    }

    void add_tail(T const& value)
    {
        __head = tail_append(__head, value);
        ++__size;
    }

    void remove()
    {
        __head = erase(__head);
        --__size;
    }

    void remove_tail()
    {
        __head = tail_erase(__head);
        --__size;
    }

    T& head()
    {
        if (empty())
            throw empty_list_exception{};

        return __head->data;
    }

    T const& head() const
    {
        return const_cast<list*>(this)->head();
    }

    T& tail()
    {
        if(empty())
            throw empty_list_exception{};

        auto* step = __head; 

        while (step->next)
        {
            step = step->next;
        }

        return step->data;
    }

    T const& tail() const
    {
        return const_cast<list*>(this)->tail();
    }

    bool empty() const
    {
        return __head == nullptr;
    }

    size_t size() const
    {
        return __size;
    }

    friend std::ostream& operator << (std::ostream& os, list const& l)
    {
        return os << l.__head;
    }
};

#endif //LIST_HPP

