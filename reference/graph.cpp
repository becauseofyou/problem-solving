#include <bits/stdc++.h>
using namespace std;

#define foreach(it,x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); ++ it)

template <typename T>
class graph {
    public:
        struct edge {
            int from;
            int to;
            T cost;
        };
        vector<edge> edges;
        vector< vector<int> > g;
        int n;
        graph(int n) : n(n) {
            g.resize(n);
        }
        virtual int add(int from, int to, T cost) = 0;
};

template <typename T>
class undigraph : public graph<T> {
    public:
        using graph<T>::edges;
        using graph<T>::g;
        using graph<T>::n;
        undigraph(int n) : graph<T>(n) {
        }
        int add(int from, int to, T cost = 1) {
            assert(0 <= from && from < n && 0 <= to && to < n);
            int id = edges.size();
            g[from].push_back(id);
            g[to].push_back(id);
            edges.push_back({from, to, cost});
            return id;
        }
};


template <typename T>
class digraph : public graph<T> {
    public:
        using graph<T>::edges;
        using graph<T>::g;
        using graph<T>::n;

        digraph(int _n) : graph<T>(_n) {
        }

        int add(int from, int to, T cost = 1) {
            assert(0 <= from && from < n && 0 <= to && to < n);
            int id = (int) edges.size();
            g[from].push_back(id);
            edges.push_back({from, to, cost});
            return id;
        }

        digraph<T> reverse() {
            digraph<T> rev(n);
            for (graph<T>::iterator it = edges.begin(); it != edges.end(); ++it) {
                rev.add(it->to, it->from, it->cost);
            }
            return rev;
        }
};



template <typename T>
vector <T> dijkstra(const graph<T> &g, int start) {
    assert(0 <= start && start < g.n);
    vector<T> dist(g.n, numeric_limits<T>::max());
    priority_queue<pair<T, int>, vector<pair<T, int> >, greater<pair<T, int> > > s;
    dist[start] = 0;
    s.push(dist[start], start);
    while (!s.empty()) {
        T expected = s.top().first;
        int i = s.top().second;
        s.pop();
        if (dist[i] != expected) {
            continue;
        }
        foreach(id, g.g[i]) {
            auto &e = g.edges[*id];
            int to = e.from ^ e.to ^ i;
            if (dist[i] + e.cost < dist[to]) {
                dist[to] = dist[i] + e.cost;
                s.push(dist[to], to);
            }
        }

    }
    return dist;
    // returns numeric_limits<T>::max() if there's no path
}
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
}
