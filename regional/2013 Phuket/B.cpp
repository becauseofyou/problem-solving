#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 100000+5;
int pri[N], pnum, a[N];
bool vis[N];

void get_prime(int n) {
    pnum = 0; vis[1] = 1;
    for(int i = 2;i <= n; i++) {
        if(!vis[i]) pri[pnum++] = i;
        for(int j = 0;j < pnum; j++) {
            if(i*pri[j] > n)    break;
            vis[i*pri[j]] = 1;
            if(i%pri[j] == 0)   break;
        }
    }
}

int main() {
    get_prime(100000);
    int n, x;
    while(scanf("%d%d", &n, &x) == 2 && n) {
        int tot = 0;
        for(int i = 0;i < pnum && pri[i] <= n; i++) {
            int cnt = 0, cur = pri[i];
            while(n/cur) {
                cnt += n/cur;
                cur *= pri[i];
            }
            a[tot++] = cnt;
        }
        ll pre = 0, now = 0, ans = 0;
        while(true) {
            now = 1;
            for(int i = 0;i < tot && a[i] >= x; i++) {
                int cur = a[i]/x+1;
                now *= cur;
            }
            if(pre == 0) {
                pre = now;
            }
            else {
                ll cur = pre - now;
                ans += cur*(cur-1)/2;
                pre = now;
            }
            if(now <= 1)    break;
            x++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}