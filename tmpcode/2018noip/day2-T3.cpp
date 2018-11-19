#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
const int MAX_POW = 19;
const long long INF = (long long) 1e12;

vector <int> e[N];
int val[N], dep[N];
int p[MAX_POW][N];
long long f[N][2], g[N][2];
struct state{
    long long a[2][2];
    void init() {
        a[0][0] = a[0][1] = a[1][1] = a[1][0] = INF;
    }
    void print() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                printf("a[%d][%d] = %lld\n", i, j, a[i][j]);
            }
        }
        puts("");
    }
}qd[MAX_POW][N];

int n, m;

void input () {
    scanf("%d%d%*s", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }
    int a, b;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &a, &b);
        a--; b--;
        e[a].push_back(b);
        e[b].push_back(a);
    }
}

void dfs(int u, int pre) {
    if(pre != -1) dep[u] = dep[pre] + 1;
    p[0][u] = pre;
    f[u][0] = 0;
    f[u][1] = val[u];
    for (auto v: e[u]) if (v != pre){
        dfs(v, u);
        f[u][0] += f[v][1];
        f[u][1] += min(f[v][0], f[v][1]);
    }
}

void rdfs(int u, int pre, long long pf0, long long pf1) {
    g[u][0] = f[u][0] + pf1;
    g[u][1] = f[u][1] + min(pf0, pf1);
    for (auto v: e[u]) if (v != pre) {
        qd[0][v].a[0][0] = INF;
        qd[0][v].a[0][1] = qd[0][v].a[1][1] = f[u][1] - min(f[v][0], f[v][1]);
        qd[0][v].a[1][0] = f[u][0] - f[v][1];
        rdfs(v, u, g[u][0] - f[v][1], g[u][1] - min(f[v][0], f[v][1]));
    }
}

state merge(const state& A, const state& B) {
    state res;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            res.a[i][j] = INF;
            for (int k = 0; k < 2; k++) {
                res.a[i][j] = min(res.a[i][j], A.a[i][k] + B.a[k][j]);
            }
        }
    }
    return res;
}

void init() {
    memset(p, -1, sizeof(p));
    dfs(0, -1);
    for (int i = 1; i < MAX_POW; i++) {
        for (int u = 0; u < n; u++) {
            p[i][u] = p[i - 1][p[i - 1][u]];
        }
    }
    rdfs(0, -1, 0, 0);
    for (int i = 1; i < MAX_POW; i++) {
        for (int u = 0; u < n; u++) {
            qd[i][u] = merge(qd[i-1][u], qd[i-1][p[i - 1][u]]);
        }
    }
}

void query() {
    int ua,x,ub,y;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d%d", &ua, &x, &ub, &y);
        ua--; ub--;
        if (dep[ua] < dep[ub]) {
            swap(ua, ub);
            swap(x, y);
        }

        int delta = dep[ua] - dep[ub];
        
        state left; left.init(); left.a[x][x] = f[ua][x];
        state right; right.init(); right.a[y][y] = f[ub][y];

        for (int i = MAX_POW - 1; i >= 0; i--) if (delta >> i & 1){
            left = merge(left, qd[i][ua]);
            ua = p[i][ua];
        }
        if (ua == ub) {
            long long res = left.a[x][y];
            int fa = p[0][ub];
            if (fa != -1) {
                long long c0 = g[fa][0] - f[ub][1];
                long long c1 = g[fa][1] - min(f[ub][0], f[ub][1]);
                if (y == 0) {
                    res += c1;
                } else {
                    res += min(c0, c1);
                }
            }
            printf("%lld\n", res >= INF ? -1 : res);
        } else {

            for (int i = MAX_POW - 1; i >= 0; i--) if (p[i][ua] != p[i][ub]) {
                left = merge(left, qd[i][ua]);
                right = merge(right, qd[i][ub]);
                ua = p[i][ua];
                ub = p[i][ub];
            }
            int lca = p[0][ua];
            long long c0 = g[lca][0] - f[ua][1] - f[ub][1];
            long long c1 = g[lca][1] - min(f[ua][0], f[ua][1]) - min(f[ub][0], f[ub][1]) ;
            c0 += left.a[x][1] + right.a[y][1];
            c1 += min(left.a[x][0], left.a[x][1]) + min(right.a[y][0], right.a[y][1]);
            printf("%lld\n", min(c0, c1) >= INF ? -1 : min(c0, c1));
        }
    }
}

int main() {
    input();
    init();
    query();
    return 0;
}
