#include <bits/stdc++.h>
using namespace std;

const int N = 2510;
int n, m;
vector <int> edge[N];
int f[3][N][N], h[3][N][N];
int g[3][3][N];
int size[N];
bool valid[3][3];
bool vis[N];
int pre[N];
int from[N];

inline void Max(int &x, int y) {
    if(y > x) {
        x = y;
    }
}

void Merge(int u, int size_u, int v, int size_v) {
    for (int color_u = 0; color_u < 3; color_u++) {
        for (int pre = 0; pre <= size_u; pre++) if (~f[color_u][u][pre]){
            for (int now = 0; now <= size_v; now++) {
                for (int color_v = 0; color_v < 3; color_v++) if (valid[color_u][color_v] && ~f[color_v][v][now]) {
                    Max (h[color_u][u][pre + now], f[color_u][u][pre] + f[color_v][v][now]);
                }
            }
        }
    }
}

//g[i][j][k] : first node's color of the sequence, last node's color of the sequence, choose k white
void DealWithCircle(int u, int size_u, vector <int> &seq) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <= size_u; j++) {
            g[i][i][j] = f[i][u][j];
        }
    }

    int sz = 0;
    for (int i = 0; i < (int)seq.size(); i++) {
        int _now = seq[i];
        for (int color_u = 0; color_u < 3; color_u++) {
            for (int color_v = 0; color_v < 3; color_v++) {
                for (int color_now = 0; color_now < 3; color_now++) if (valid[color_v][color_now]) {
                    for (int pre = 0; pre <= size_u; pre++) if (~g[color_u][color_v][pre]) {
                        for (int now = 0; now <= size[_now]; now++) if (~f[color_now][_now][now]){
                            Max(g[color_u][color_now][pre + now], g[color_u][color_v][pre] + f[color_now][_now][now]);
                        }
                    }
                }
            }
        }
    }
    for (int color_u = 0; color_u < 3; color_u++) {
        for (int color_v = 0; color_v < 3; color_v++) {
            for ()
        }
    }
}


void Dfs (int u, int fa) {
    pre[u] = fa;
    vis[u] = true;
    f[0][u][0] = 0;
    f[1][u][1] = 0; // put white
    f[2][u][0] = 1; // put black
    int sz = 1;
    from[u] = -1;
    for (int v : edge[u])  {
        if (!vis[v]) {
            Dfs (v, u);
            if (from[u] == -1) {
                Merge(u, sz, v, size[v]);
            } else {
                vector <int> circle;
                int end = from[u];
                while (end != u) {
                    circle.push_back(end);
                    end = pre[end];
                }
                reverse(circle.begin(), circle.end());
                DealWithCircle(u, sz, circle);
                from[u] = -1;
            }
            sz += size[v];
            for (int color = 0; color < 3; color++) {
                for (int i = 0; i <= sz; i++) {
                    f[color][u][i] = h[color][u][i];
                    h[color][u][i] = -1;
                }
            }
        } else if (v != fa){
            from[u] = v;
        }
    } 
    size[u] = sz;
}
int main () {
    valid[0][1] = valid[0][0] = valid[0][2] = true;
    valid[1][0] = valid[1][1] = true;
    valid[2][0] = valid[2][2] = true;
    memset (h, -1, sizeof(h));
    memset (f, -1, sizeof(f));
    scanf("%d%d", &n, &m);
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    memset (f, -1, sizeof(f));
    Dfs (1, 0);
    int ret = 0;
    for (int c = 0; c < 3; c++) {
        for (int i = 0; i <= n; i++) if (~f[c][1][i]){
            printf("f[%d][1][%d]=%d\n", c, i, f[c][1][i]);
        }
    }
    printf("ret = %d\n" ,ret);
    return 0;
}
