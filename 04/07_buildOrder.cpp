
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::cout, std::cerr, std::endl, std::cin;
using std::string;
using std::vector;
using std::unordered_map;

#include "graph.hpp"

using project_t = string;
using graph_t = graph<project_t>;
struct dep_t
{
    int s, d;

    dep_t(int _s, int _d)
        :s(_s),d(_d)
    { }

    dep_t(dep_t const&) = default;
    dep_t(dep_t&&) = default;
};

unordered_map<string, int> projects;

auto buildGraph(vector<dep_t> const& dep)
{
    graph_t g;

    return g;
}


auto findBuildOrder(graph_t const& g)
{
    vector<project_t> ps;

    return ps;
}


void pr(vector<string>&& cont)
{
    for (auto const& v: cont)
        cout << v << ' ';
    cout << endl;
}


int main()
{
    vector<dep_t> dep;

    int N;
    cin >> N;

    for (size_t i = 0u; i < N; ++i)
    {
        string s, d;
        cin >> s >> d;

        if (projects.find(s)
        projects[s]

        dep.emplace_back(s ,d);
    }

    auto g = buildGraph(dep);

    pr(findBuildOrder(g));
}


