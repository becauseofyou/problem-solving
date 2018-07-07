// srm 449 div1 500pt is recomended 
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,n) for(int i=0;i<n;i++)
#define rev(i,b) for(int i=b;i>=0;i--)
const int mod = 1000000007;
const int m = 3;
char buf[3][10010];
int n,f[2][1<<m][2];
void Add(int &x,int y) {
    x += y;
    if(x >= mod)x-=mod;
}
void solve() {
    int cur=0,nxt=1,lim=1<<m;
    int st=0;
    rep(i,3)if(buf[i][0]!='.')st|=1<<(2-i);
    f[0][st][0] = 1;
    rep(i,n) rev(j,m-1){
        memset(f[nxt],0,sizeof(f[nxt]));
        rep(mask,lim){
            rep(G,2)if(f[cur][mask][G]){
                int add = f[cur][mask][G],g;
                int to = mask;
                if(buf[j][i+1]!='.') to |= 1<<m;
                if(mask&1) { Add(f[nxt][to>>1][G],add);continue;}
                g = G;
                if(j-1 >= 0 && !(mask&2)) {
                    if(j+1 < m)  g |= (buf[j+1][i] == 'O');
                    if(j-2 >= 0) g |= (buf[j-2][i] == 'O');
                    Add(f[nxt][(to|2)>>1][g],add);
                }
                g = G;
                if(i-1 >= 0) g |= (buf[j][i-1] == 'O');
                if(i+2 < n)  g |= (buf[j][i+2] == 'O');
                if(buf[j][i+1]=='.')
                    Add(f[nxt][(mask|1<<m)>>1][g],add);
            }
        }
        std::swap(cur,nxt);
    }
    printf("%d\n",f[cur][lim-1][1]);
}
int main() {
    scanf("%d",&n);
    for(int i = 0; i < 3; i++) scanf("%s",buf[i]);
    solve();
    return 0;
}
