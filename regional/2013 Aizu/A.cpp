#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int dp[22][12][222],n,m,s;

void init() {
        dp[0][0][0] = 1;
        for (int i = 0; i <= 20; i ++) {
                for (int j = 0; j <= 10; j ++) {
                        for (int k = 0; k <= 155; k ++) if (dp[i][j][k]) {
                                dp[i+1][j][k] += dp[i][j][k];
                                dp[i+1][j+1][k+i+1] += dp[i][j][k];
                        }
                }
        }
}

int main() {
        init();
        while (scanf("%d%d%d",&n,&m,&s)==3) {
                if (!n && !m && !s) break;
                printf("%d\n",dp[n][m][s]);
        }
        return 0;
}