#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 20000+5;
int dis[N], sum[N], a[N], n;

void update(int x) {
        while(x > 0) {
                sum[x]++;
                x -= x&-x;
        }
}

int query(int x) {
        int ret = 0;
        while(x <= n) {
                ret += sum[x];
                x += x&-x;
        }
        return ret;
}

int main() {
        int t, k, cas = 1;
        scanf("%d", &t);
        while(t--) {
                scanf("%d%d", &n, &k);
                for(int i = 1;i <= n; i++)      sum[i] = 0;
                for(int i = 1;i <= (n+k-1)/k; i++)     dis[i] = 0;
                int a1 = 0, a2 = 0;
                for(int i = 1;i <= n; i++) {
                        scanf("%d", &a[i]);
                        int x = (a[i]+k-1)/k;
                        a1 += query(x*k+1);
                        update(a[i]);
                        int l = x*k-(k-1), r = x*k;
                        r = min(r, n);
                        int mn;
 //                       printf("i = %d l = %d r = %d\n", i, l, r);
                        if(i < l)       mn = l-i;
                        else if(i > r)  mn = i-r;
                        else    mn = 0;
                        dis[x] = max(dis[x], mn);
                }
                for(int i = 1;i <= (n+k-1)/k; i++)     a2 = max(a2, dis[i]);
//                printf("a1 = %d a2 = %d\n", a1, a2);
                printf("Case %d: %d\n", cas++, a1 - a2);
        }
        return 0;
}