#include <bits/stdc++.h>
using namespace std;
//滚动数组
//dp[i][j]: 前i个物品 组合成j体积 的 最大价值

const int N = 110;
const int MAXV = 1010;
int v[N], c[N];
int dp[MAXV];

int main () {
    int T, m;
    scanf("%d%d", &T, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &v[i], &c[i]);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = T; j >= v[i]; j--) {
            dp[j] = max(dp[j], dp[j - v[i]] + c[i]);
        }
    }
    int ret = 0;
    for (int i = 0; i <= T; i++) if(dp[i] > ret){
        ret = dp[i];
    }
    printf("%d\n", ret);
    return 0;
}


