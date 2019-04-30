#include <iostream>
#include <vector>
#include "graph.hpp"

using std::vector;
using std::cout, std::cin, std::endl, std::cerr;

template<class N, class V>
vector<int> DFS(graph<N,V> const& g, int s, int d)
{
    auto const size = g.size();
    if (size == 0 || g[s].empty())
        return vector<int>();

    struct frame
    {
        int node_id;
        int edge_id;

        frame(int n, int e): node_id(n), edge_id(e) {}
    };

    vector<frame> stack;//.reserve(size);
    vector<bool> visited(size, false);
    vector<int> path;

    stack.emplace_back(s,0);
    visited[s] = true;
    path.emplace_back(s);
    
    while (!stack.empty())
    {
        auto& [node_id, edge_id] = stack.back();
        if (edge_id < g[node_id].size())
        {
            auto dest_node_id = g[node_id][edge_id].node_id;
            if (!visited[dest_node_id])
            {
                stack.emplace_back(dest_node_id, 0);
                visited[dest_node_id] = true;
                path.push_back(dest_node_id);
                if (dest_node_id == d)
                {
                    return path;
                }
                continue;
            }
            edge_id++; 
            continue;
        }
        path.pop_back();
        stack.pop_back();
    }
}

void pr(vector<int>&& v)
{
    for (auto const e: v)
        cout << e <<  ' ';
    cout << endl;
}

int main() 
{
    std::ios::sync_with_stdio(false);

    int D; //destination
    cin >> D;

    int N;
    cin >> N; //number of nodes

    graph g(N);

    cin >> N; //number of edges

    while (N--)
    {
        int s, d;
        cin >> s >> d;
        g.edge_d(s, d);
    }

    cout << g << endl;

    pr(DFS(g, 0, D));
}

