/**
 *    author:  tourist
 *    created: 26.09.2017 21:41:25       
 **/
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class graph {
    public:
        struct edge {
            int from;
            int to;
            T cost;
        };

        vector <edge> edges;
        vector < vector <int> > g;
        int n;

        graph(int n) : n(n) {
            g.resize(n);
        }

        virtual void add(int from, int to, T cost) = 0;
};

template <typename T>
class undigraph : public graph<T> {
    public:
        using graph<T>::edges;
        using graph<T>::g;
        using graph<T>::n;

        undigraph(int n) : graph<T>(n) {
        }

        void add(int from, int to, T cost = 1) {
            assert(0 <= from && from < n && 0 <= to && to < n);
            g[from].push_back(edges.size());
            g[to].push_back(edges.size());
            edges.push_back({from, to, cost});
        }
};

class dsu {
    public:
        vector <int> p;
        int n;

        dsu(int n) : n(n) {
            p.resize(n);
            iota(p.begin(), p.end(), 0);
        }

        inline int get(int x) {
            return (x == p[x] ? x : (p[x] = get(p[x])));
        }

        inline bool unite(int x, int y) {
            x = get(x);
            y = get(y);
            if (x != y) {
                p[x] = y;
                return true;
            }
            return false;
        }
};

template <typename T>
vector< vector<int> > find_cycles(const graph<T> &g, int bound = 1 << 30) {
    vector<int> was(g.n, -1);
    vector<int> st;
    vector< vector<int> > cycles;
    function<void(int, int)> dfs = [&g, &was, &st, &cycles, &dfs, &bound](int v, int pe) {
        if ((int) cycles.size() >= bound) {
            return;
        }
        was[v] = st.size();
        for (int id : g.g[v]) {
            if (id == pe) {
                continue;
            }
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            if (was[to] >= 0) {
                vector<int> cycle(1, id);
                for (int j = was[to]; j < (int) st.size(); j++) {
                    cycle.push_back(st[j]);
                }
                cycles.push_back(cycle);
                if ((int) cycles.size() >= bound) {
                    return;
                }
                continue;
            }
            if (was[to] == -1) {
                st.push_back(id);
                dfs(to, id);
                st.pop_back();
            }
        }
        was[v] = -2;
    };
    for (int i = 0; i < g.n; i++) {
        if (was[i] == -1) {
            dfs(i, -1);
        }
    }
    return cycles;
    // returns at most bound cycles (given by edge ids)
    // digraph: finds at least one cycle in every connected component
    // undigraph: finds cycle basis
}

int main() {
    return 0;
}
