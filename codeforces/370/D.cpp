/*
 *
 题意：
 给你a b k t
 表示两个人A B一开始的数分别为a b，t轮内每一轮可以选择-k -> k之间的整数累加
 最后有多少种选法使得最后的和sum(A) > sum(B)
 
 做法：数据范围都不大，很显然这题是要dp，然后就是dp转移过程的优化了。
 f[t][i]表示进行了t轮 和为i的方案数
 f[t][i] =  sum(f[t - 1][i - k] -> f[t - 1][i + k])
 所以当前阶段的一个状态是由前面状态的一段连续区间的和得来的，因此可以联想到每次处理出前缀和来算这个值
 转移的复杂度就变成了O(1)
 复杂度为 O(t * k )
 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
int f[200010], sum[200010];

void Add(int &x, int y) {
    x += y;
    if(x >= MOD) {
        x -= MOD;
    }
}

int lim;
inline int Sum(int id) {
    if (id < 0) {
        return 0;
    }
    if(id > lim) {
        return sum[lim];
    }
    return sum[id];
}

int main() {
    int a, b, k, t;
    cin >> a >> b >> k >> t;
    memset(f, 0, sizeof(f));
    lim = 2 * k * t;
    f[k*t] = 1;
    for (int i = 1; i <= lim; i++) {
        sum[i] = sum[i - 1];
        Add(sum[i], f[i]);
    }
    for (int i = 0; i < t; i++) {
        for (int s = lim; s >= 0; s--)  {
            int l = s - k, r = s + k;
            f[s] = ( (Sum(r) - Sum(l - 1) ) % MOD + MOD) % MOD;
        }
        memset(sum, 0, sizeof(sum));
        sum[0] = f[0];
        for (int j = 1; j <= lim; j++) {
            sum[j] = sum[j - 1];
            Add(sum[j], f[j]);
        }
    }
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i <= lim; i++) {
        sum[i] = f[i];
        if (i) {
            Add(sum[i], sum[i - 1]);
        }
    }
    int ret = 0;
    for (int i = 0; i <= lim; i++) {
        int id = i + (a - b) - 1;
        Add(ret, 1LL * f[i] * Sum(i + (a - b) - 1) % MOD);
    }
    /*
    int tmp = 0;
    for (int i = 0; i <= lim; i++) {
        for (int j = 0; j <= lim; j++) if(a + i > b + j){
            tmp += f[i] * f[j];
        }
    }
    */
    printf("%d\n" , ret);
    return 0;
}
