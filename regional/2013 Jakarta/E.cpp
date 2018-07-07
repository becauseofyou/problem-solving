#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

#define mp make_pair
#define pb push_back
#define snuke(it,x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); it ++)
typedef long long lld;
typedef pair<int,int> PII;

const int N = 101000;
int n,m,idx[N],deg[N],tot,up[N],down[N],que[N],qf,qe,dis[N];
bool vis[N];
vector<int> G[N];

struct Block {
        char c;
        int x,y,z;
        void read(int id = 0) {
                char s[2];
                scanf("%s%d%d%d",s,&x,&y,&z); x --; y --; z --;
                c = s[0];
                if (c=='F') {
                        idx[x] = id;
                } else {
                        idx[x] = idx[y] = id;
                }
        }
}block[N];

void build() {
        tot = 0;
        memset(vis,0,sizeof(vis));
        qf = qe = 0;
        vis[0] = 1;
        que[qe++] = 0;
        up[0] = tot ++;
        down[0] = tot ++;
        while (qf!=qe) {
                int u = que[qf++];
                if (u==n-1) continue;
                int id = idx[u];
                int x = block[id].x;
                int y = block[id].y;
                int z = block[id].z;
                if (block[id].c=='F') {
                        up[y] = up[x];
                        down[z] = down[x];
                        down[y] = up[z] = tot ++;
                        vis[y] = 1;
                        que[qe++] = y;
                        vis[z] = 1;
                        que[qe++] = z;
                } else {
                        if (!vis[x] || !vis[y]) continue;
                        up[z] = up[x];
                        down[z] = down[y];
                        if (!vis[z]) {  // 特别注意J操作，z有两个来源，但只能入队列一次，否则出错
                                vis[z] = 1;
                                que[qe++] = z;
                        }
                }
        }
        for (int i = 0; i < N; i ++) G[i].clear();
        memset(deg,0,sizeof(deg));
        for (int i = 0; i < n; i ++) {
                G[up[i]].pb(down[i]);
                deg[down[i]] ++;
        }
}

int work() {
        build();
        qf = qe = 0;
        que[qe++] = 0;
        dis[0] = 0;
        while (qf!=qe) {
                int u = que[qf++];
                snuke(it,G[u]) {
                        int v = *it;
                        deg[v] --;
                        if (deg[v]==0) {
                                dis[v] = dis[u]+1;
                                que[qe++] = v;
                        }
                }
        }
        int ret = 0;
        for (int i = 0; i < tot; i ++) {
                ret = max(ret,dis[i]);
        }
        return ret;
}


int main() {
        int cas,ca = 0;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d%d",&n,&m);
                for (int i = 0; i < m; i ++) {
                        block[i].read(i);
                }
                printf("Case #%d: %d\n",++ca,work());
        }
        return 0;
}