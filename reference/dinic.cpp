/*
 * 结构体或类名：Max_Flow
 * 变量名: maxFlow;
 * 函数名 : Max_flow()
 *
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N = 20010;
const int M = 500010;
const int INF = ~0u >> 2;
template<class T>
struct Max_Flow {
    int s, t, n;
    int Q[N], sign;
    int head[N], level[N], cur[N], pre[N];
    int nxt[M], pnt[M], E;
    T cap[M];
    void Init(int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
        E = 0;
        std::fill(head, head + n, -1);
    }
    void Add_edge(int from, int to, T c) {
        pnt[E] = to;
        cap[E] = c;
        nxt[E] = head[from];
        head[from] = E++;

        pnt[E] = from;
        cap[E] = 0;
        nxt[E] = head[to];
        head[to] = E++;
    }
    bool Bfs(int s, int t) {
        sign = t;
        std::fill(level, level + n, -1);
        int *front = Q, *tail = Q;
        *tail++ = t; level[t] = 0;
        while(front < tail && level[s] == -1) {
            int u = *front++;
            for(int e = head[u]; e != -1; e = nxt[e]) {
                if(cap[e ^ 1] > 0 && level[pnt[e]] < 0) {
                    level[pnt[e]] = level[u] + 1;
                    *tail ++ = pnt[e];
                }
            }
        }
        return level[s] != -1;
    }
    void Push(int t, T &flow) {
        T mi = INF;
        int p = pre[t];
        for(int p = pre[t]; p != -1; p = pre[pnt[p ^ 1]]) {
            mi = std::min(mi, cap[p]);
        }
        for(int p = pre[t]; p != -1; p = pre[pnt[p ^ 1]]) {
            cap[p] -= mi;
            if(!cap[p]) {
                sign = pnt[p ^ 1];
            }
            cap[p ^ 1] += mi;
        }
        flow += mi;
    }
    void Dfs(int u, int t, T &flow) {
        if(u == t) {
            Push(t, flow);
            return ;
        }
        for(int &e = cur[u]; e != -1; e = nxt[e]) {
            if(cap[e] > 0 && level[u] - 1 == level[pnt[e]]) {
                pre[pnt[e]] = e;
                Dfs(pnt[e], t, flow);
                if(level[sign] > level[u]) {
                    return ;
                }
                sign = t;
            }
        }
    }
    T Dinic() {
        pre[s] = -1;
        T flow = 0;
        while(Bfs(s, t)) {
            std::copy(head, head + n, cur);
            Dfs(s, t, flow);
        }
        return flow;
    }
};


template <typename T>
class max_flow {

int source, sink;

public:
	struct edge {
		int from, to;
		T cap;
	};

	vector <edge> e;
	vector <vector <int> > g;
	vector <int> cur, d, q, pre;
	int n, blocked;

	max_flow() {}
	max_flow(int n) {
		this->n = n;
		g.resize(n);
		d.resize(n);
		cur.assign(n, 0);
		q.resize(n);
		pre.resize(n);
	}

	void add_edge(int from, int to, T cap) {
//		printf("%d %d %d\n", from, to, cap);
		e.pb({from, to, cap});
		e.pb({to, from, 0});
		g[from].pb((int)e.size() - 2);
		g[to].pb((int)e.size() - 1);
	}

	bool bfs() {
		d.assign(n, -1);
		d[sink] = 0;			              
		int h = 0, t = 0;
		q[t++] = sink;
		while (h < t) {
			int u = q[h++];
			foreach (it, g[u]) {
				int id = *it;
				if (e[id ^ 1].cap > 0 && d[e[id].to] < 0) {
					d[e[id].to] = d[u] + 1;
					q[t++] = e[id].to;
				}
			}
		}
		return d[source] != -1;
	}

	void push(int t, T &flow) {
		T minimum = numeric_limits<T> ::max();
		for (int id = pre[t]; ~id; id = pre[e[id ^ 1].to]) {
			checkmin(minimum, e[id].cap);
		}
		for (int id = pre[t]; ~id; id = pre[e[id ^ 1].to]) {
			e[id].cap -= minimum;
			if (!e[id].cap) {
				blocked = e[id ^ 1].to;
			}
			e[id ^ 1].cap += minimum;
		}
		flow += minimum;
	}

	void dfs(int u, int t, T &flow) {
		if (u == t) {
			push(t, flow);
			return ;
		}
		for (int &id = cur[u]; id < sz(g[u]); id++) {
			edge &it = e[g[u][id]];
			if (it.cap > 0 && d[u] - 1 == d[it.to]) {
				pre[it.to] = g[u][id];
				dfs (it.to, t, flow);
				if (d[blocked] > d[u]) {
					return;
				}
				blocked = t;
			}
		}
	}

	T dinic(int s, int t) {
		this->source = s;
		this->sink = t;
	 	pre[s] = -1;
	 	T flow = 0;
	 	while (bfs()) {
	 		cur.assign(n, 0);
	 		dfs(s, t, flow);
	 	}
	 	return flow;
	}
};

