#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 3000+5;
const int INF = (int)1e9;
int dp[N][N][2], a[N];

int main() {
        int n, p, l;
        while(scanf("%d%d%d", &n, &p, &l) == 3 && n) {
                int mx = 0;
                for(int i = 1;i <= n; i++)      scanf("%d", &a[i]), mx += a[i];
                for(int i = 0;i <= n; i++)
                        for(int j = 0;j <= n; j++)
                                dp[i][j][0] = dp[i][j][1] = INF;
                dp[0][0][0] = 0;
                int cur = 0;
                for(int i = 1;i <= n; i++) {
                        int now = cur + a[i];
                        for(int j = 0;j < i; j++) {
                                int left = cur/p*p, right = (now+p-1)/p*p;
                                if(right > mx) right = mx;
                                if(dp[i-1][j][0] != INF) {
                                        dp[i][j+1][1] = min(dp[i][j+1][1], dp[i-1][j][0]+right-left);
                                        dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][0]);
                                }
                                left = (cur+p-1)/p*p; right = (now+p-1)/p*p;
                                if(right > mx)      right = mx;
                                if(left > mx)        left = mx;
                                if(dp[i-1][j][1] != INF) {
                                        dp[i][j+1][1] = min(dp[i][j+1][1], dp[i-1][j][1] + right-left);
                                        if(right > left)        
                                                dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][1]);
                                }
                        }
                        for(int j = 0;j <= i; j++) {
                                if(dp[i][j][0] > l)     dp[i][j][0] = INF;
                                if(dp[i][j][1] > l)     dp[i][j][1] = INF;
                        }
                        cur = now;
                }
                int ans = 0;
                for(int i = 1;i <= n; i++) if(dp[n][i][0] <= l || dp[n][i][1] <= l)
                        ans = i;
                printf("%d\n", ans);
        }
        return 0;
}