#include <cstdio>
char ans[5000010];
int tot;
int Abs(int x) {
    if(x < 0) x = -x;
    return x;
}
int d;
const int dd[2] = {-1,1};
const char dir[2] = {'L','R'};
void go(int &now,int ter,int tim)
{
    if(now == ter) return ;
    if(Abs(now-ter) <= tim) {
        for(int i = 0; i < Abs(now-ter); i++) ans[tot++]=dir[d];
        now = ter;
    } else {
        for(int i = 0; i < tim; i++) ans[tot++]=dir[d];
        now += dd[d] * tim;
    }
}
int main()
{
    int n, m, s, f, t, a, b;
    scanf("%d%d%d%d",&n,&m,&s,&f);
    int now = s,pre = 0;
    d = now < f ? 1 : 0;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d",&t,&a,&b);
        if(now == f) continue;
        if(t - pre - 1 > 0)  go(now,f,t-pre-1);
        if(now == f) continue;
        int next = now + dd[d];
        if(now >= a && now <= b) ans[tot++] = 'X';
        else if(next >= a && next <= b) ans[tot++] = 'X';
        else     now = next,ans[tot++]=dir[d];
        pre = t;
    }
    if(now != f) go(now,f,10000000);
    for(int i = 0; i < tot; i++) printf("%c",ans[i]);
    return 0;
}
