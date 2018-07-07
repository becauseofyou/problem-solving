#include <cstdio>
#include <cstring>
#include <algorithm>
using std::sort;
using std::fill;
using std::max;
using std::unique;
using std::lower_bound;
const int N = 330010;
struct point {
    int x,y,z;
    int id;
    bool operator < (const point& b) const {
        if(x == b.x) {
            if(y == b.y) return z > b.z;
            else return y > b.y;
        }
        return x < b.x;
    }
    inline void in() {
        scanf("%d%d%d",&x,&y,&z);
    }
}p[N],g[N];
int num[N];
int f[N];
inline int cmpy(point a,point b){
    return  a.y < b.y;
}
struct BIT{
    int n;
    int c[1000010];
    inline void init(int n) {
        this->n = n;
    }
    inline void insert(int x, int add) {
        for(; x <= 1000000; x += x & -x) if(add > c[x]) c[x] = add;
    }
    inline int ask(int x) {
        int ret = 0;
        for(; x > 0; x -= x & -x) if(c[x] > ret) ret = c[x];
        return ret;
    }
    inline void clear(int x) {
        for(; x <= 1000000; x += x & -x) c[x] = 0;
    }
}ta;
void update(int l1, int r1, int l2, int r2) {
    sort(g + l1, g + r1 + 1, cmpy);
    sort(g + l2, g + r2 + 1, cmpy);
    int pt = l1;
    for(int i = l2; i <= r2; i++) {
        while(pt <= r1 && g[pt].y < g[i].y){
            ta.insert(g[pt].z, f[g[pt].id]);
            pt++;
        }
        int opt=ta.ask(g[i].z - 1);
        if(opt + 1 > f[g[i].id]) {
            f[g[i].id] = opt + 1;
        }
    }
    for(int i = l1; i <= r1; i++) ta.clear(g[i].z);
}
void solve(int l,int r)
{
 //   printf("l=%d r=%d\n",l,r);
    if(l == r) {    
        return ; 
    }
    int mid = (l + r) >> 1;
    solve(l,mid);
    for(int i = l; i <= r; i++)    g[i] = p[i];
    update(l, mid, mid + 1, r);
    solve(mid+1,r);
}
int M, a, b, C;
int main()
{
    int t,m,nn,A,B;
    while(scanf("%d%d%d%d",&m,&nn,&A,&B) && (m + nn + A + B))
    {
        a = A; b = B;
        C = ~(1 << 31);
        M = (1 << 16) - 1;
        for(int i = 1; i <= m; i++) {
            p[i].in();
            p[i].id = i;
            p[i].z++;
        }
        for(int i = m + 1; i <= m + nn; i++) {
            a = 36969 * (a & M) + (a >> 16);
            b = 18000 * (b & M) + (b >> 16);
            int x = (C & ((a << 16) + b)) % 1000000;
            a = 36969 * (a & M) + (a >> 16);
            b = 18000 * (b & M) + (b >> 16);
            int y = (C & ((a << 16) + b)) % 1000000;
            a = 36969 * (a & M) + (a >> 16);
            b = 18000 * (b & M) + (b >> 16);
            int z = (C & ((a << 16) + b)) % 1000000;
            p[i].x = x;
            p[i].y = y;
            p[i].z = z + 1;
            p[i].id = i;
        }
        int n = m + nn;
        sort(p+1,p+n+1); 
        fill(f, f + n + 1, 1);
        solve(1, n);
        int ret = 1;
        for(int i = 1; i <= n; i++) ret = max(ret, f[i]);
        printf("%d\n",ret);
        /*  static int dp[N];
            fill(dp, dp + n + 1, 1);
            int ans= 1;
            for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
            if(p[i].x < p[j].x && p[i].y < p[j].y && p[i].z < p[j].z) {
            dp[j] = max(dp[j], dp[i] + 1);
            }
            if(dp[j] > ans) ans = dp[j];
            }
            }
            printf("%d\n",ans);
            */
    }
    return 0;
}
