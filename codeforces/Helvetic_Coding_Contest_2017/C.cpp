#include <bits/stdc++.h>
using namespace std;
int sumFlow;
const int MAXN = 502;
const int MAXM = 10002;
const int INF = 1000000;
struct Edge{
    int u, v, cap, cost;
    int next;
}edge[MAXM<<2];
int NE;
int head[MAXN], dist[MAXN], pp[MAXN];
bool vis[MAXN];
void init(){
    NE = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int cap, int cost){
    edge[NE].u = u; edge[NE].v = v; edge[NE].cap = cap; edge[NE].cost = cost;
    edge[NE].next = head[u]; head[u] = NE++;
    edge[NE].u = v; edge[NE].v = u; edge[NE].cap = 0; edge[NE].cost = -cost;
    edge[NE].next = head[v]; head[v] = NE++;
}
bool SPFA(int s, int t, int n){
    int i, u, v;
    queue <int> qu;
    memset(vis,false,sizeof(vis));
    memset(pp,-1,sizeof(pp));
    for(i = 0; i <= n; i++) dist[i] = INF;
    vis[s] = true; dist[s] = 0;
    qu.push(s);
    while(!qu.empty()) {
        u = qu.front(); qu.pop(); vis[u] = false;
        for(i = head[u]; i != -1; i = edge[i].next){
            v = edge[i].v;
            if(edge[i].cap && dist[v] > dist[u] + edge[i].cost){
                dist[v] = dist[u] + edge[i].cost;
                pp[v] = i;
                if(!vis[v]){
                    qu.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    if(dist[t] == INF) return false;
    return true;
}
int MCMF(int s, int t, int n, int k) {
    int flow = 0; 
    int minflow, mincost;
    mincost = 0;
    while(SPFA(s, t, n)){
        if(dist[t] >= 0) {
            break;
        }
        minflow = INF + 1;
        for(int i = pp[t]; i != -1; i = pp[edge[i].u])
            if(edge[i].cap < minflow)
                minflow = edge[i].cap;
        flow += minflow;
        for(int i = pp[t]; i != -1; i = pp[edge[i].u]){
            edge[i].cap -= minflow;
            edge[i^1].cap += minflow;
        } 
        mincost += dist[t] * minflow;
        if(flow == k) {
            break;
        }
    }
    return mincost;
}

int a[MAXN], c[MAXN];
int main() {
    int n, k;
    scanf("%d%d", &n, &k); k = min(k, n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);a[i]--;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }
    int S = 2 * n, T = S + 1;
    init(); 
    int ret = 0;
    for(int i = 0; i < n; i++) {
        addedge(i, i + n, 1, -INF);
        addedge(S, i, 1, 0);
        addedge(i + n, T, 1, 0);
        ret += c[a[i]];
        for(int j = i + 1; j < n; j++) if(a[i] == a[j]) {
            addedge(i + n, j, 1, -c[a[j]]);
        } else {
            addedge(i + n, j, 1, 0);
        }
    }
    printf("%d\n", ret + MCMF(S, T, T + 1, k) + n * INF );
    return 0;
}
