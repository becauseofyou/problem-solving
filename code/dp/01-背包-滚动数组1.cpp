#include <bits/stdc++.h>
using namespace std;
//滚动数组
//dp[i][j]: 前i个物品 组合成j体积 的 最大价值

const int N = 110;
const int MAXV = 1010;
int v[N], c[N];
int dp[2][MAXV];

int main () {
    int T, m;
    scanf("%d%d", &T, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &v[i], &c[i]);
    }
    int now = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= T; j++) {
            dp[now][j] = dp[now ^ 1][j];
            if (j >= v[i]) {
                dp[now][j] = max(dp[now][j], dp[now ^ 1][j - v[i]] + c[i]);
            }
        }
        now ^= 1;
        memset(dp[now], 0, sizeof(dp[now]));
    }

    int ret = 0;
    for (int i = 0; i <= T; i++) if (dp[now^1][i] > ret){
        ret = dp[now^1][i];
    }
    printf("%d\n", ret);
    return 0;
}


