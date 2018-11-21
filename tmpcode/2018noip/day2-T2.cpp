#include <bits/stdc++.h>
using namespace std;



const int mod = (int)1e9+7;

vector <pair<int,int> > v[100];

int a[8][8];
int cnt;
int n, m;

bool check() {
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) if (a[i - 1][j] == a[i][j - 1]){
            for (int xie = i + j + 1; xie < n + m - 1; xie++) {
                int col = -1;
                int state = 0;
                for (int k = 0; k < v[xie].size(); k++) {
                    auto it = v[xie][k];
                    if (it.first >= i && it.second >= j) {
                        state |= (1 << a[it.first][it.second]);
                    }
                    if (state == 3) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void dfs(int tot, int now) {
    //printf("tot=%d now=%d\n", tot, now);
    if (now == tot) {
        if (check()) {
            cnt++;
        }
        return ;
    }
    for (int i = 0; i < v[now].size(); i++) {
        pair<int,int> it = v[now][i];
        a[it.first][it.second] = 1;
    }
    dfs(tot, now + 1);
    for (int i = 0; i < v[now].size(); i++) {
        pair<int,int> it = v[now][i];
        a[it.first][it.second] = 0;
        dfs(tot, now + 1);
    }
}

int brute(int n, int m) {
    ::n = n;
    ::m = m;
    cnt = 0;
    for (int i = 0; i < 100; i++) v[i].clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            v[i+j].push_back(make_pair(i, j));
        }
    }
    dfs(n + m - 1, 0);
    return cnt;
}
//首先发现f[n][m] = 3 * f[n][m - 1](m>=n-2)
//那么我们只需要搞出8*9以内的就万事大吉
//首先开个O2大力打出8*8的表，然后你会发现f[n][n+1] = f[n][n] * 3 + d
//d是个等比数列，然后8*9的答案可以推算出来
//8×8需要跑一小会，搜索写的好一点可以更快地打出8*8
//所以这道题考察搜索与找规律能力 囧
 int biao[][10] = {
 {2,4,8,16,32,64,128,256},
 {4,12,36,108,324,972,2916,8748},
 {8,36,112,336,1008,3024,9072,27216},
 {16,108,336,912,2688,8064,24192,72576},
 {32,324,1008,2688,7136,21312,63936,191808},
 {64,972,3024,8064,21312,56768,170112,510336},
 {128,2916,9072,24192,63936,170112,453504,1360128},
 {256,8748,27216,72576,191808,510336,1360128,3626752, 10879488}
};

int pow_mod(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) {
            ret = 1LL * ret * a % mod;
        }
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ret;
}

int main () {
    /*
    for (int i = 8; i <= 8; i++) {
        printf("i=%d\n", i);
        cout << '{';
        for (int j = 8; j <= 8; j++) {
 //           printf("i=%d j=%d\n", i, j);
            printf("%d, \n", brute(i, j));
        }
        cout << '}' << endl;
    }*/
    biao[6][8] = biao[6][7] * 3;
    biao[6][9] = biao[6][8] * 3;
    biao[7][9] = biao[7][8] * 3;
    int n, m;
    cin >> n >> m;
    if (n == 1) {
        cout << pow_mod(2, m) << endl;
        return 0;
    }
    n --;
    m --;
    if (m >= 7 && m >= n + 2) {
        cout << 1LL * biao[n][n + 2] * pow_mod(3, m - n - 2) % mod;
    } else {
        cout << biao[n][m]  << endl;
    }
    return 0;
}
