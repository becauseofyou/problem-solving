#include <bits/stdc++.h>

using namespace std;
const int maxn=1051;
const int inf=0x7fffffff/2-1;
int n,m,tot=0,h[maxn],dp[maxn][maxn];
struct edge{int to,next,w;}G[100001];
int ans[maxn],sum[maxn],K,tmp[11],S;
struct point{int col,w;}p[maxn];
bool vis[maxn];

bool check(int s){
    for (int i=1;i<=10;++i) tmp[i]=0;
    for (int i=1;i<=K;++i) 
        if (s&(1<<(i-1))) tmp[p[i].col]++;
    for (int i=1;i<=10;++i) if (tmp[i]&&tmp[i]!=sum[i]) return 0;
    return 1;
}

void add(int x,int y,int z){
    G[++tot].to=y;G[tot].next=h[x];h[x]=tot;G[tot].w=z;
    G[++tot].to=x;G[tot].next=h[y];h[y]=tot;G[tot].w=z;
}

void spfa(int s){
    queue<int>q; 
    for (int i=1;i<=n;++i) vis[i]=1,q.push(i);
    while (!q.empty()){
        int u=q.front(); q.pop(); vis[u]=0;
        for (int i=h[u];i;i=G[i].next){
            int v=G[i].to;
            if (dp[u][s]+G[i].w<dp[v][s]){
                dp[v][s]=dp[u][s]+G[i].w;
                if (!vis[v]) vis[v]=1,q.push(v);
            }
        }
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=m;++i){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
    }
    S=1<<K;
    for (int i=1;i<=n;++i)
        for (int j=0;j<S;++j) dp[i][j]=inf;
    for (int s=0;s<S;++s) ans[s]=inf;
    for (int i=1;i<=K;++i) scanf("%d%d",&p[i].col,&p[i].w),sum[p[i].col]++;
    for (int i=1;i<=K;++i) dp[p[i].w][1<<(i-1)]=0;
    for (int s=0;s<S;++s){
        for (int i=1;i<=n;++i) 
            for (int s0=s;s0;s0=(s0-1)&s)
                dp[i][s]=min(dp[i][s],dp[i][s0]+dp[i][s^s0]);
        spfa(s);
    }
    for (int s=0;s<S;++s)
        for (int i=1;i<=n;++i) ans[s]=min(ans[s],dp[i][s]);
    for (int s=0;s<S;++s)
        if (check(s))
            for (int s0=s;s0;s0=(s0-1)&s)
                if (check(s0)) 
                    ans[s]=min(ans[s],ans[s0]+ans[s^s0]);
    printf("%d",ans[(1<<K)-1]);
}