
动态规划
dynamic programming

lis: longest increasing subsequence
状态：f[i] : 以第i个数结尾的的 LIS的长度

f[i] = 1;


f[1]-> f[i]

subproblem
f[i+1] = max(f[j] + 1) //对于所有的能接上来的j 挑选一个最大的

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i]) {
                checkmin(f[i], f[j] + 1);
            }
        }
    }
