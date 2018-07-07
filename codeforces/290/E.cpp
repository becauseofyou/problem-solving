#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
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
        void gao() {
        }
};
Max_Flow<int> *G = new Max_Flow<int> ();
bool flag[20010];
void init()
{
        for(int i = 2; i <= 20000; i++) {
                for(int j = 2 * i; j <= 20000; j+=i) {
                        flag[j] = true;
                }
        }
}
vector<int> adj[222];
bool vis[222];
vector<int> v ;
void dfs(int u)
{
        vis[u] = true;
        v.push_back(u);
        for(int i = 0; i < adj[u].size(); i++) {
                int to = adj[u][i];
                if(!vis[to]){
                        dfs(to);
                }
        }
}
int main()
{
        init();
        int n, a[222];
        scanf("%d", &n);
        G->Init(n + 2, 0, n + 1);
        int odd = 0, even = 0;
        for(int i = 1; i <= n; i++) {
                scanf("%d", &a[i]);
                if(a[i] % 2 == 0) {
                        G->Add_edge(0, i, 2);
                        even++;
                } else {
                        odd++;
                        G->Add_edge(i, n + 1, 2);
                }
                for(int j = 1; j < i; j++) {
                        if(!flag[a[i] + a[j]]) {
                                if(a[i] % 2 == 0)
                                        G->Add_edge(i, j, 1);
                                else G->Add_edge(j , i, 1);
                        }
                }
        }
        if(odd != even) {
                puts("Impossible");
                return 0;
        }
        int ret = G->Dinic();
        if(ret  != odd * 2) {
                puts("Impossible");
                return 0;
        }
        for(int u = 1; u <= n; u++) {
                if(a[u] % 2 == 0) {
                        for(int i = G->head[u]; i != -1; i = G->nxt[i]) {
                                int to = G->pnt[i];
                                if(to != 0 && G->cap[i] == 0) {
                                        adj[u].push_back(to);
                                        adj[to].push_back(u);
                                }
                        }
                }
        }
        memset(vis, false, sizeof(vis));
        vector<vector<int> > ans;
        for(int i = 1; i <= n; i++) {
                if(!vis[i]) {
                        v.clear();
                        dfs(i);
                        ans.push_back(v);
                }
        }
        printf("%d\n", ans.size());
        for(int i = 0; i < ans.size(); i++) {
                printf("%d", ans[i].size());
                for(int j = 0; j < ans[i].size(); j++) {
                        printf(" %d" ,ans[i][j]);
                }
                puts("");
        }
        return 0;
}
