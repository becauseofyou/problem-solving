#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1250+5;
double dp[N][N][2];
bool vis[N][N];
int c[N], w[N];

int main() {
        int t, cas = 1;
        scanf("%d", &t);
        while(t--) {
                int n, m;
                scanf("%d%d", &n, &m);
                for(int i = 1;i <= n; i++)      scanf("%d", &c[i]);
                for(int i = 1;i <= n; i++)      scanf("%d", &w[i]);
                for(int i = 0;i <= n; i++)
                        for(int j = 0;j <= n; j++)
                                vis[i][j] = 0;
                vis[0][0] = 1;
                dp[0][0][0] = dp[0][0][1] = 1.0;
                for(int i = 1;i <= n; i++) {
                        for(int j = 0;j < i; j++) if(vis[i-1][j]) {
                                for(int k = 0;k < 2; k++) {
                                        double cur = dp[i-1][j][k]*(1.0 - 2.0*w[i]/100);
                                        if(!vis[i][j]) {
                                                dp[i][j][0] = dp[i][j][1] = cur;
                                                vis[i][j] = 1;
                                        }
                                        else {
                                                dp[i][j][0] = min(dp[i][j][0], cur);
                                                dp[i][j][1] = max(dp[i][j][1], cur);
//                                                if(i == 1)      printf("%d %f %f\n", j, dp[i][j][0], dp[i][j][1]);
                                        }
                                        cur = dp[i-1][j][k]*(2.0*c[i]/100-1.0);
                                        if(!vis[i][j+1]) {
                                                dp[i][j+1][0] = dp[i][j+1][1] = cur;
                                                vis[i][j+1] = 1;
                                        }
                                        else {
                                                dp[i][j+1][0] = min(dp[i][j+1][0], cur);
                                                dp[i][j+1][1] = max(dp[i][j+1][1], cur);
                                        }
                                }
                        }
                }
                double ans = dp[n][0][0];
                for(int i = 0;i <= m; i++)      ans = min(ans, dp[n][i][0]);
                printf("Case #%d: %.3f\n", cas++, ans*15000);
        }
        return 0;
}