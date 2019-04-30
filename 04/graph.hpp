#if !defined GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

template<class N=int, class E=int>
struct graph
{
    struct edge {
        int node_id; // destination
        E info;
        int rev_node_id; //for undirect graphs keeps (s->d) (d->s)
        edge(int id, E i): node_id(id), info(i) {}
    };

    struct node: std::vector<edge>
    {
        N value;
    };

    std::vector<node> nodes;

    graph(int ns = 0): nodes(ns) {}

    void edge_d(int s, int d, E info = 1)
    {
        nodes[s].emplace_back(d, info);
    }

    void edge_u(int s, int d, E info = 1)
    {
        edge_d(s, d);
        auto const s_rev = nodes[s].size() - 1;
        edge_d(d, s);
        auto const d_rev = nodes[d].size() - 1;
        nodes[s][s_rev].rev_node_id = d_rev;
        nodes[d][d_rev].rev_node_id = s_rev;
    }

    bool is_connected(int s, int d) // O(n)
    {
        for (auto edge_id: nodes[s])
        {
            if (d == nodes[s][edge_id].node_id)
                return  true;
        }

        return false;
    }

    auto& operator[](int id)
    {
        return nodes[id];
    }


    auto const& operator[](int id) const
    {
        return nodes[id];
    }

    auto size() const
    {
        return nodes.size();
    }


    friend std::ostream& operator << (std::ostream& os, graph const& g)
    {
#if defined LIST
        os << g.nodes.size() << '\n';

        for (auto s = 0u; s < g.nodes.size(); ++s)
        {
            for (auto i = 0u; i < g.nodes[s].size(); ++i)
            {
                auto const& n = g.nodes[s][i];
                os << s << " -> " << n.node_id << " (" << n.info << ")\n";
            }
        }
#else
        for (auto s = 0u; s < g.nodes.size(); ++s)
        {
            os << s << ':';
            for (auto i = 0u; i < g.nodes[s].size(); ++i)
            {
                auto const& n = g.nodes[s][i];
                os << n.node_id << '(' << n.info << ") ";
            }
            os << '\n';
        }

#endif
        return os;
    }

};

#endif //GRAPH_HPP
