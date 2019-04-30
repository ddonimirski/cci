#include <iostream>
#include <vector>
#include <deque>
#include "graph.hpp"

using std::vector;
using std::deque;
using std::cout, std::cin, std::endl, std::cerr;

vector<int> show_path(vector<int> const& p, int s, int d)
{
    vector<int> ret;
    ret.emplace_back(d);
    while (p[d] != s)
    {
        if (p[d] == -1 || p[d] == d)
        {
            return vector<int>{};
        }

        ret.emplace_back(p[d]);
        d = p[d];
    }

    ret.emplace_back(s);

    return ret;
}

template<class N, class V>
vector<int> BFS(graph<N,V> const& g, int s, int d)
{
   vector<int> path(g.size(),-1); 
   vector<bool> visited(g.size());
   deque<int> nodes;

   nodes.push_back(s);
   path[0] = 0;

   while (!nodes.empty())
   {
       auto node_id = nodes.front();
       nodes.pop_front();
       visited[node_id] = true;

       for (auto edge_id = 0u; edge_id < g[node_id].size(); ++edge_id)
       {
           auto ch_id = g[node_id][edge_id].node_id;
           if (!visited[ch_id])
           {
               path[ch_id] = node_id;
               if (ch_id == d)
               {
                   return show_path(path, s, d);
               }
               nodes.push_back(ch_id);
           }
       }
   }

   path.clear(); // not found
   return path;
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

    pr(BFS(g, 0, D));
}
