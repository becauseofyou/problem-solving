#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

const int N = 110;
const int INF = 0x3f3f3f3f;
int G[N][N],n,m,K,match[N],rec[N],tot,dis[N],vis[N];

bool expath(int u) {
        rec[tot++] = u;
        if (vis[u]) return true;
        vis[u] = 1;
        for (int i = 0; i < K; i ++) {
                if (i!=u && i!=match[u] && !vis[i]) {
                        int t = match[i];
                        if (dis[t] < dis[u]+G[u][i]-G[i][t]) {
                                dis[t] = dis[u]+G[u][i]-G[i][t];
                                if (expath(t)) return true;
                        }
                }
        }
        tot --;
        vis[u] = false;
        return false;
}

void work() {
        scanf("%d%d%d",&n,&m,&K);
        memset(G,INF,sizeof(G));
        for (int i = 0; i < n; i ++) {
                G[i][i] = 0;
        }
        for (int i = 0; i < m; i ++) {
                int a,b,c;
                scanf("%d%d%d",&a,&b,&c); a --; b --;
                G[a][b] = G[b][a] = min(G[a][b],c);
        }
        if (K&1) {
                puts("Impossible");
                return ;
        }
        for (int k = 0; k < n; k ++) {
                for (int i = 0; i < n; i ++) {
                        for (int j = 0; j < n; j ++) {
                                G[i][j] = min(G[i][j],G[i][k]+G[k][j]);
                        }
                }
        }

        for (int i = 0; i < K; i ++) {
                G[i][i] = -INF;
                for (int j = 0; j < K; j ++) {
                        G[i][j] *= -1;
                }
        }
        for (int i = 0; i < K; i += 2) {
                match[i] = i+1;
                match[i+1] = i;
        }
        int cnt = 0;
        while (true) {
                memset(dis,0,sizeof(dis));
                memset(vis,0,sizeof(vis));
                tot = 0;
                bool ok = false;
                for (int i = 0; i < K; i ++) {
                        if (expath(i)) {
                                ok = true;
                                int t = match[rec[tot-1]];
                                int j = tot-2;
                                while (rec[j]!=rec[tot-1]) {
                                        match[t] = rec[j];
                                        swap(t,match[rec[j]]);
                                        j --;
                                }
                                match[t] = rec[j];
                                match[rec[j]] = t;
                                break;
                        }
                }
                if (!ok && ++cnt>=3) {
                        break;
                }
        }
        int ans = 0;
        for (int i = 0; i < K; i ++) {
                ans -= G[i][match[i]];
        }
        printf("%d\n",ans>>1);
}

int main() {
        int cas,ca = 0;
        scanf("%d",&cas);
        while (cas--) {
                printf("Case %d: ",++ca);
                work();
        }
        return 0;
}