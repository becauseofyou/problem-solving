#include <cstdio>
#include <vector>
#include <iostream>

typedef long long LL;
const int N = 1000005;

int n, m;
bool vis[N], vis_e[N], flg[N];
int fa[N], fw[N], va[N << 1], id[N << 1], q[N];
LL f[N], g[N], dis[N << 1], ans;
int cva[N];
std::vector<int> cir[N];

int yun = 1, las[N], to[N << 1], wi[N << 1], pre[N << 1];
inline void Add(int a, int b, int c) {
  to[++yun] = b; wi[yun] = c; pre[yun] = las[a]; las[a] = yun;
}

inline int Read(int &x) {
  x = 0; static char c;
  for (c = getchar(); c < '0' || c > '9'; c = getchar());
  for (; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + c - '0', c = getchar());
}

void Dfs_init(int x) {
  vis[x] = 1;
  for (int i = las[x]; i; i = pre[i]) {
    if (vis_e[i >> 1]) continue;
    vis_e[i >> 1] = 1;
    if (vis[to[i]]) {
      cir[++m].push_back(to[i]);
      cva[m] = wi[i];
      flg[to[i]] = 1;
      for (int t = x; t != to[i]; t = fa[t]) {
        cir[m].push_back(t);
        flg[t] = 1;
      }
    } else {
      fa[to[i]] = x;
      fw[to[i]] = wi[i];
      Dfs_init(to[i]);
    }
  }
}
void Dfs_cal(int x, int Fa) {
  for (int i = las[x]; i; i = pre[i]) {
    if (to[i] == Fa || flg[to[i]]) continue;
    Dfs_cal(to[i], x);
    f[x] = std::max(f[x], f[to[i]]);
    f[x] = std::max(f[x], g[x] + g[to[i]] + wi[i]);
    g[x] = std::max(g[x], g[to[i]] + wi[i]);
  }
}
LL Solve(int k, LL re = 0) {
  int nm = (int)cir[k].size();
  for (int i = 0; i < nm; ++i) {
    re = std::max(re, f[cir[k][i]]);
    id[i + 1] = id[i + 1 + nm] = cir[k][i];
    va[i + 1] = va[i + 1 + nm] = (i == 0)? cva[k] : fw[cir[k][i]];
  }
  for (int i = 1; i <= nm << 1; ++i) {
    dis[i] = dis[i - 1] + va[i - 1];
  }
  for (int i = 1, nl = 1, nr = 0; i <= nm << 1; ++i) {
    while (nl <= nr && i - q[nl] > nm - 1) ++nl;
    if (q[nl] != i && nl <= nr) {
      re = std::max(re, g[id[i]] + dis[i] + g[id[q[nl]]] - dis[q[nl]]);
    }
    while (nl <= nr && g[id[i]] - dis[i] >= g[id[q[nr]]] - dis[q[nr]]) --nr;
    q[++nr] = i;
  }
  return re;
}

int main() {
  scanf("%d", &n);
  for (int i = 1, x, y, z; i <= n; ++i) {
    Read(x); Read(y); Read(z);
    Add(x, y, z); Add(y, x, z);
  }
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      Dfs_init(i);
      for (int j = 0; j < (int)cir[m].size(); ++j) {
        Dfs_cal(cir[m][j], 0);
      }
      ans += Solve(m);
      cir[m].clear();
    }
  }
  printf("%lld\n", ans);

  return 0;
}