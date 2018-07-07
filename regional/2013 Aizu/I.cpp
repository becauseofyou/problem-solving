#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = (int)1e9;
const int N = 1000+5;
int dp[N*500], a[N], b[N], vis[N], sum[N];

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 1;i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 1;i <= n; i++) {
            vis[i] = 1;
            for(int j = 1;j <= n; j++) if(i!=j && a[i]%a[j] == 0 && a[i]!=a[j]) {
                int cur = a[i]/a[j];
                if(((cur-1)&cur) == 0)  {
                    vis[i] = 0;
                    break;
                }
            }
        }
        int ans = 0;
        for(int i = 1;i <= n; i++) if(vis[i]){
            int tot = 0;
            for(int j = 1;j <= n; j++) if(a[j]%a[i] == 0) {
                int cur = a[j]/a[i];
                if(((cur-1)&cur) == 0)  b[++tot] = cur;
            }
            for(int j = 1;j <= tot; j++)    sum[j] = sum[j-1] + b[j];
            for(int j = 0;j <= sum[tot]; j++)   dp[j] = -INF;
            dp[0] = 0;
            for(int j = 1;j <= tot; j++) {
                for(int k = sum[j];k >= b[j]; k--) if(((k-b[j])&(b[j]-1)) == 0)
                    dp[k] = max(dp[k], dp[k-b[j]] + 1);
            }
            for(int j = 1;j <= sum[tot]; j++) if(dp[j] > 0 && ((j-1)&j) == 0)
                ans = max(ans, dp[j]);
            for(int j = 1;j <= n; j++) if(a[i] == a[j])
                vis[j] = 0;
        }
        printf("%d\n", ans);
    }
    return 0;
}