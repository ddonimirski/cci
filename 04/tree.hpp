#if !defined TREE__HPP
#define TREE__HPP

#include <vector>

template<class N=1>
struct tree
{
    struct node: std::vector<node>
    {
        
        int N;
    };

    node root;
};

#endif //TREE__HPP

