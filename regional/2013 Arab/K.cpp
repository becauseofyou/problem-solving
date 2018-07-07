#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 110;
const int M = 1110;
const int INF = 0x3f3f3f3f;

int n,m,L,dp[M],pos[N];
int dis[N],que[N],qf,qe;

int spfa(int s) {
        qf = qe = 0;
        que[qe++] = s;
        memset(dis,INF,sizeof(dis));
        dis[s] = 0;
        while (qf!=qe) {
                int u = que[qf++];
                for (int i = 0; i < n; i ++) {
                        int d = abs(pos[i]-pos[u]);
                        if (dp[d]!=INF && dis[i]==INF) {
                                dis[i] = dis[u]+1;
                                que[qe++] = i;
                        }
                }
        }
        return dis[n-1]==INF ? -1 : dis[n-1];
}

int main() {
        int cas;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d%d%d",&n,&m,&L);
                memset(dp,INF,sizeof(dp));
                for (int i = 0; i < n; i ++) {
                        scanf("%d",&pos[i]);
                }
                sort(pos,pos+n);
                dp[0] = 0;
                for (int i = 0; i < m; i ++) {
                        int c,v;
                        scanf("%d%d",&c,&v);
                        for (int j = 1000-v; j >= 0; j --) if (dp[j]!=INF) {
                                dp[j+v] = min(dp[j+v],dp[j]+c);
                        }
                }
                for (int i = 0; i <= 1000; i ++) {
                        if (dp[i]>L) dp[i] = INF;
                }
                printf("%d\n",spfa(0));
        }
        return 0;
}