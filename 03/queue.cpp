#include <iostream>
#include "queue.hpp"
#include <deque>
#include <string>

using std::cout, std::cin, std::endl;


struct animal
{
    int type;
    std::string name;

    friend std::ostream& operator<< (std::ostream& os, animal const& v);
};


struct animals
{
    struct base_t
    {
        int order;
        std::string name;

    };

    int __c_order = 0;

    queue<base_t, queue_policy<base_t, std::deque<base_t>>> __dog;
    queue<base_t, queue_policy<base_t, std::deque<base_t>>> __cat;

    enum types {
        DOG,
        CAT,
    };

    void enqueue(int type, std::string const& name)
    {
        if (type == types::DOG)
        {
            __dog.enqueue({__c_order++, name});
        }
        else
        {
            __cat.enqueue({__c_order++, name});
        }
    }

    animal dequeueAny()
    {
        if(__cat.empty())
        {
            return dequeueDog();
        }
        else if (__dog.empty())
        {
            return dequeueCat();
        }

        auto cat = __cat.front();
        auto dog = __dog.front();

        if (dog.order < cat.order)
        {
            __dog.dequeue();
            return std::move(animal{types::DOG, dog.name});
        }
        else
        {
            __cat.dequeue();
            return std::move(animal{types::CAT, cat.name});
        }

        return std::move(animal{-1, "None"});
    }

    animal dequeueDog()
    {
        auto dog = __dog.front();
        __dog.dequeue();
        return std::move(animal{DOG, dog.name});
    }

    animal dequeueCat()
    {
        auto cat = __cat.front();
        __cat.dequeue();
        return std::move(animal{CAT, cat.name});
    }

    bool empty() const
    {
        return __cat.empty() && __dog.empty();
    }

    bool noDogs() const
    {
        return __dog.empty();
    }

    bool noCats() const
    {
        return __cat.empty();
    }
};


int main()
{

    animals q;

    q.enqueue(animals::types::DOG, "burek");
    q.enqueue(animals::types::DOG, "norek");
    q.enqueue(animals::types::CAT, "puma");
    q.enqueue(animals::types::DOG, "rurka");
    q.enqueue(animals::types::CAT, "misia");
    

    while (!q.empty())
    {
        auto v = q.dequeueAny();
        cout << v << ", ";
    }
    cout << endl;


    q.enqueue(animals::types::DOG, "burek");
    q.enqueue(animals::types::DOG, "norek");
    q.enqueue(animals::types::CAT, "puma");
    q.enqueue(animals::types::CAT, "kotek");
    q.enqueue(animals::types::DOG, "rurka");
    q.enqueue(animals::types::CAT, "misia");

    if (!q.noDogs())
    {
        auto v = q.dequeueDog();
        cout << v << ' ';
    }
    cout << endl;

    if (!q.noCats())
    {
        auto v = q.dequeueCat();
        cout << v << ' ';
    }
    cout << endl;

    while (!q.noDogs())
    {
        auto v = q.dequeueDog();
        cout << v << ' ';
    }
    cout << endl;

    while (!q.noCats())
    {
        auto v = q.dequeueCat();
        cout << v << ' ';
    }
    cout << endl;
}

std::ostream& operator<< (std::ostream& os, animal const& v)
{
    return os << ((animals::types::DOG == v.type) ? "dog " : "cat ") << v.name ;
}
