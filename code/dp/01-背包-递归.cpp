#include <bits/stdc++.h>
using namespace std;

//dp[i][j]: 前i个物品 组合成j体积 的 最大价值

const int N = 110;
const int MAXV = 1010;
int v[N], c[N];
int dp[N][MAXV];

int dfs(int i, int j) {
    if (i == 0) {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    dp[i][j] = max(dp[i][j], dfs(i - 1, j));
    if (j >= v[i]) {
        dp[i][j] = max(dp[i][j], dfs(i - 1, j - v[i]) + c[i]);
    }
    return dp[i][j];
}

int main () {
    int T, m;
    scanf("%d%d", &T, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &v[i], &c[i]);
    }
    memset(dp, -1, sizeof(dp));
    int ret = 0;
    for (int i = 0; i <= T; i++) {
        ret = max(ret, dfs(m, i));
    }
    printf("%d\n", ret);
    return 0;
}


