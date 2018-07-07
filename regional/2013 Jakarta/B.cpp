/*
 * memo[i][j] : 纽约正在发第i个包的同时，雅加达正在发第j个包
 * 当两者的发送时间的差距大于D的时候相对顺序是变不了的
 * 小于D的时候就可以有两种转移
 */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
const int N = 50010;
const int MOD = 1000000009;
int D;
int memo[N][210];
int a[N];
int b[N];
int n, m;
int rec(int i, int j) {
    while (true) {//肯定确定的相对关系
        bool update = false;
        while (i < n && b[j] - a[i] > D) i++, update = true;
        while (j < m && a[i] - b[j] > D) j++, update = true;
        if (!update) break;
    }
    if (i == n || j == m) return 1;
    int delta = a[i] - b[j] + 100;
    int &ret = memo[i][delta];
    if (ret != -1) return ret; else ret = 0;
    if (a[i] - b[j] < D) ret += rec(i + 1, j);  
    if (b[j] - a[i] < D) ret += rec(i, j + 1); 
    ret %= MOD;
    return ret;
}
int main() {
    int t, ca = 1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &m, &D);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 0; i < m; i++) {
            scanf("%d", &b[i]);
        }
        memset(memo, -1, sizeof(memo));
        printf("Case #%d: %d\n", ca++, rec(0, 0));
    }
    return 0;
}