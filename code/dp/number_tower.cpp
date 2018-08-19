
数塔问题

dp[i][j]:到了第i行第j列，最大的和
int solve(int i, int j) {
    if (i == 1 && j == 1) {

    }
    if(dp[i][j] != -1) {
        return dp[i][j];
    }
    int a = solve(i - 1, j - 1);
    int b = solve(i - 1, j);
    dp[i][j] = max(a, b) + a[i][j];
    return dp[i][j];
}
