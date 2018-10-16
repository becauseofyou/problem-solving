#include <bits/stdc++.h>

using namespace std;


template <typename T>
void checkmax(T &x, T y) {
    if (y > x) {
        x = y;
    }
}

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
class dfs_one_loop_tree:  public graph<T> {
    public: 
        using graph<T>::edges;
        using graph<T>::g;
        using graph<T>::n;
        vector <int> st;
        vector <int> circle;
        vector <int> pos;

        dfs_one_loop_tree(int n): graph<T>(n) {
            pos.resize(n, -1);
        }

        void find_circle(int u, int preid) {
            if ((int) circle.size() > 0) {
                return;
            }
            st.push_back(u);
            pos[u] = (int)st.size() - 1;
            for (int id : g[u]) {
                if (id == preid) {
                    continue;
                }
                auto &e = edges[id];
                int v = e.from ^ e.to ^ u;
                if (pos[v] >= 0) {
                    for (int j = pos[v]; j < (int) st.size(); j++) {
                        circle.push_back(st[j]);
                    }
                    return ;
                }
                if (pos[v] == -1) {
                    find_circle(v, id);
                    if (circle.size()) {
                        return ;
                    }
                }
            }
            st.pop_back();
            pos[u] = -2;
        }

        void find_circle() {
            find_circle(0, -1);
        }

};


template<typename T>
class dfs_forest: public dfs_one_loop_tree<T> {
    public:

        using dfs_one_loop_tree<T>::edges;
        using dfs_one_loop_tree<T>::g;
        using dfs_one_loop_tree<T>::n;
        using dfs_one_loop_tree<T>::circle;

        vector <long long> dist; //circle to sequence
        vector <bool> ban;
        long long longest;

        dfs_forest(int n) : dfs_one_loop_tree<T>(n) {
            ban.resize(n, false);
            longest = 0;
        }

        void setban() {
            for (int u: circle) {
                ban[u] = true;
            }
        }

        long long dfs_once(int u, int preid) {
            long long mx = 0;
            for (int id: g[u]) {
                auto &e = edges[id];
                int v = e.from ^ e.to ^ u;
                if (id == preid || ban[v]) {
                    continue;
                }
                long long tmp = dfs_once(v, id);
                checkmax(longest, mx + tmp + e.cost);
                checkmax(mx, tmp + e.cost);
            }
            return mx;
        }

        template<typename M>
            vector<M> get_circle_value() {
                setban();
                vector <M> ret(2 * circle.size());
                for (int i = 0; i < (int)circle.size(); i++) {
                    ret[i] = dfs_once(circle[i], -1);
                }
                copy(ret.begin(), ret.begin() + circle.size(), ret.begin() + circle.size());
                return ret;
            }

        //cut circle, double the sequence
        template<typename M>
            vector<M> get_circle_dist() {
                int sz = (int) circle.size();
                vector <M> dist(2 * sz);
                vector <bool> used(2 * n, false);
                for (int i = 0; i < sz; i++) {
                    int u = circle[i];
                    for (int id: g[u]) {
                        auto &e = edges[id];
                        int v = e.from^e.to^u;
                        if (v == circle[(i + 1) % sz] && !used[id]) {
                            used[id] = true;
                            dist[(i + 1) % sz] = e.cost;
                            break;
                        }
                    }
                }
                copy(dist.begin(), dist.begin() + sz, dist.begin() + sz);
                for (int i = 0; i < 2*sz; i++) {
                    if(i)dist[i] += dist[i - 1];
                }
                return dist;
            }

};

//in most case T is a pair, T.first is value, T.second is index 
template<typename T>
class dan{
    public :
        dan(int n) : fr(0), ed(0){
            q.resize(n);
            fr = 0;
            ed = 0;
        }
        vector<T> q;
        int fr, ed;
        bool empty() {
            return fr >= ed;
        }
        T back() {
            return q[ed - 1];
        }
        T front() {
            return q[fr];
        }
        void pop_back() {
            ed--;
        }
        void pop_front() {
            fr++;
        }
        void push_back(T ele) {
            q[ed++] = ele;
        }
        void insert(T ele) {
            while (!empty() && back().first <= ele.first) {
                pop_back();
            }
            push_back(ele);
        }
};

namespace solver {
    long long result = 0;
    template<typename T>
        void solve(vector <T> value, vector <T> dist) {
            int n = (int)value.size();
            if (n == 2) { // self loop
                printf("%lld\n", result + 1);
                return ;
            }
            long long limit_length = dist[n / 2 - 1] / 2;
            //cerr << "n = " << n << endl;
            //cerr << "limit = " << limit_length << endl;
            dan<pair<long long, long long> > Q(n);
            for (int i = 0; i < n; i++) {
                while(!Q.empty() && dist[i] - Q.front().second > limit_length) {
                    Q.pop_front();
                }
                if (!Q.empty()) {
                    checkmax(result, value[i] + dist[i] + Q.front().first);
                }
                Q.insert(make_pair(value[i] - dist[i], dist[i]));
            }
            printf("%lld\n", result + 1);
        }
}

int main () {
    int n;
    scanf("%d", &n);
    dfs_forest<int> g(n);
    int x, y, z;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        x--; y--;
        g.add(x, y, z);
    }
    g.find_circle();
    vector <long long> value = g.get_circle_value<long long>();
    checkmax(solver::result, g.longest);
    vector <long long> dist = g.get_circle_dist<long long>();
    solver::solve(value, dist);
    return 0;
}
