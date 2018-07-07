#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;


const int N = 20200;
int head[N],etot,n,ans,sz[N];
struct edge {int v,next;}g[505000];

void add_edge(int u,int v) {
        g[etot].v = v; g[etot].next = head[u]; head[u] = etot ++;
}

void dfs(int u,int fa) {
        sz[u] = 1;
        int cnt = 0;
        int val = 0;
        for (int i = head[u]; i != -1; i = g[i].next) {
                int v = g[i].v;
                if (v==fa) continue;
                dfs(v,u);
                val += cnt*sz[v];
                cnt += sz[v];
        }
        val += cnt*(n-1-cnt);
        ans = max(ans,val);
        sz[u] += cnt;
}

int main() {
        int cas,ca = 0;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d",&n);
                memset(head,-1,sizeof(head)); etot = 0;
                for (int i = 0; i < n-1; i ++) {
                        int a,b;
                        scanf("%d%d",&a,&b); a --; b --;
                        add_edge(a,b);
                        add_edge(b,a);
                }
                ans = 0;
                dfs(0,-1);
                printf("Case #%d: %d\n",++ca,ans);
        }
        return 0;
}