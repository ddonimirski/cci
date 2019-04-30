#include <iostream>
#include "graph.hpp"

using std::cout, std::cin, std::endl, std::cerr;


int main() 
{
    std::ios::sync_with_stdio(false);

    bool D; // direct
    cin >> D;

    int N;
    cin >> N;

    graph g(N);

    cin >> N;

    while (N--)
    {
        int s, d;
        cin >> s >> d;
        if (D)
            g.edge_d(s, d);
        else
            g.edge_u(s, d);
    }

    cout << g << endl;

}
