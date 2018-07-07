#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
        int n, m;
        while(scanf("%d%d", &n, &m) == 2 && n) {
                if(n > m)       swap(n, m);
                ll ans = 0;
                for(int i = 1;i <= n; i += 2)
                        ans += (ll)(n-i+1)*(m-i+1);
                for(int i = 3;i <= n; i += 2) {
                        ans += (ll)(i-1)*(n-i+1)*(m-i+1);
                }
                printf("%lld\n", ans);
        }
        return 0;
}

