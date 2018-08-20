#include <bits/stdc++.h>
using namespace std;

//dp[i][j]: 前i个物品 组合成j体积 的 最大价值

const int N = 110;
const int MAXV = 1010;
int v[N], c[N];
int dp[N][MAXV];

int main () {
    int T, m;
    scanf("%d%d", &T, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &v[i], &c[i]);
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= T; j++) {
            dp[i][j] = dp[i - 1][j]; //不选第i个
            if (j >= v[i]) { // 选择第i个试试看 取最大
                dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i]] + c[i]);
            }
        }
    }
    int ret = 0;
    for (int i = 0; i <= T; i++) if(dp[m][i] > ret) {
        ret = dp[m][i];
    }
    printf("%d\n", ret);
    return 0;
}


