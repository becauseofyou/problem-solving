#include <bits/stdc++.h>
using namespace std;

long long dp[33][2];

int main() {
    dp[1][0] = 1;
    dp[1][1] = 3;
    for (int i = 2; i <= 30; i++) {
        dp[i][0] += dp[i - 1][1];
        dp[i][1] += (dp[i - 1][0] + dp[i - 1][1]) * 3;
    }
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp[n][0] + dp[n][1]);
    return 0;
}
