#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;


const int N = 550,INF = 0x3f3f3f3f;
int n,m,W,c,C,head[N],etot,dis[N],ans,inq[N],cnt[N],que[N],qf,qe,tims[N],tim;
struct edge {int v,w,next;} g[501000];

void add_edge(int u,int v,int w) {
   //     printf("u = %d,v = %d,w = %d\n",u,v,w);
        g[etot].v = v; g[etot].next = head[u]; g[etot].w = w; head[u] = etot ++;
}

bool spfa(int s) {
        qf = qe = 0;
        que[qe++] = s;
        dis[s] = 0;
        tim ++;
        while (qf!=qe) {
                int u = que[qf++];
                if (qf==N) qf = 0;
                inq[u] = 0;
                tims[u] = tim;
                for (int i = head[u]; i != -1; i = g[i].next) {
                        int v = g[i].v;
                        int w = g[i].w;
                        if (dis[v]>dis[u]+w) {
                                dis[v] = dis[u]+w;
                                if (!inq[v]) {
                                        que[qe++] = v;
                                        if (qe==N) qe = 0;
                                        inq[v] = 1;
                                        cnt[v] ++;
                                        if (cnt[v]>=n) return false;
                                }
                        }
                }
        }
        int vmin = INF,vmax = -INF;
        for (int i = 0; i <= n; i ++) if (tims[i]==tim) {
                vmin = min(vmin,dis[i]);
                vmax = max(vmax,dis[i]);
        }
        ans = min(ans,vmax-vmin);
        return true;
}

bool work(int _s) {
        memset(dis,INF,sizeof(dis));
        memset(inq,0,sizeof(inq));
        memset(cnt,0,sizeof(cnt));
        memset(tims,0,sizeof(tims));
        tim = 0;
        ans = INF;
        if (!spfa(_s)) return false;
        printf("%d\n",ans);
        return true;
}

int main() {
        while (scanf("%d%d%d%d%d",&n,&m,&W,&c,&C)==5 && n) {
                memset(head,-1,sizeof(head)); etot = 0;
                int _s = n;
                for (int i = 0; i < m; i ++) {
                        int a,b;
                        scanf("%d%d",&a,&b); a --; b --;
                        add_edge(a,b,-c);
                        add_edge(b,a,C);
                        add_edge(_s,a,c);
                        add_edge(_s,b,0);
                }
                for (int i = 0; i < W; i ++) {
                        int a,b;
                        scanf("%d%d",&a,&b); a --; b --;
                        add_edge(a,b,0);
                        add_edge(b,a,0);
                }
                if (!work(_s)) {
                        puts("Impossible");
                }
        }
        return 0;
}