#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int md = (int) 1e9 + 7;

// 前i个数，j个在上面，i-K+1 -> i的上下情况
// 近的数在低位

void add(int &x, int y) {
    x += y;
    if (x >= md) {
        x -= md;
    }
}


int dp[2*N][N][1 << 10];
int cnt [1 << 10], c[2*N][N];
int full;

void U(int i, int j, int mask) {
    add(dp[i + 1][j + 1][(mask << 1) & full], dp[i][j][mask]); // 放上面
}

void D(int i, int j, int mask) {
    add(dp[i + 1][j][( (mask << 1) & full) | 1], dp[i][j][mask]); // 放下面
}


int C(int n, int k) {
	if (c[n][k] != -1) return c[n][k];
    if (n == k) {
        return 1;
    }
    if (k == 0) {
        return 1;
    }
    return c[n][k] = (C(n - 1, k - 1) + C(n - 1, k)) % md ;
}

int main() {
    int n, K;
    cin >> n >> K;
    if (K == 1) { //随便放特判掉
    	memset(c, -1, sizeof(c));
        cout << C(2 * n, n) << endl;
        return 0;
    }
    K--;
    full = (1 << K) - 1;
    dp[K][0][full] = 1;
    dp[K][K][0] = 1;
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 10; j++) {
            cnt[i] += (i>>j&1) > 0;
        }
    }
    for (int i = K; i <= 2*n; i++) {
        for (int j = 0; j <= i && j <= n; j++) {
            for (int mask = 0; mask <= full; mask++) if(dp[i][j][mask]){
                if (j == i - j) {
                    U(i, j, mask);
                    D(i, j, mask);
                } else if (j > i - j) { //上面的数列比较长，那么在下面放的时候需要判断上面配对的数是否合法
                    U(i, j, mask);
                    int up = K - cnt[mask];//最近的K-1个数在上面有up个,即二进制中0的个数
                    //配对的数不是最近的K - 1个数
                    if (j - (i - j) > up ) {
                        D(i, j, mask);
                    }
                } else { //同理
                    D(i , j, mask);
                    int down = cnt[mask];
                    if ((i - j) - j > down) {
                        U(i, j, mask);
                    }
                }
            }
        }
    }
    
    int ret = 0;
    for (int mask = 0; mask <= full; mask++) {
        add (ret, dp[2*n][n][mask]);
    }
    cout << ret << endl;
    return 0;
}
