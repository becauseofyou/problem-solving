#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int MOD = (int) 1e9 + 7;

int deg[N];
int dp[N][N][N]; //total number of nodes, depth, number of nodes in the last level. 
int bino[N][N];
int g[N][N][N];
inline void Add(int &x, int y) {
  if(y < 0) {
    printf("y=%d\n", y); 
  }
  if(x == -1) {
    x = y;
  } else {
    x += y;
    if(x >= MOD) {
      x -= MOD;
    } 
  }
}

//cnt1 cnt2, choose k to connect the next level
int h[55][55][55];
//cnt1 cnt2   self connect
int c[55][55];

void init() {
  for(int i = 0; i <= 50; i++) {
    bino[i][0] = bino[i][i] = 1;
    for(int j = 1; j < i; j++) {
      bino[i][j] = (bino[i - 1][j] + bino[i - 1][j - 1]) % MOD;
    }
  }
  for(int cnt1 = 0; cnt1 <= 50; cnt1++)  {
    for(int cnt2 = 0; cnt1 + cnt2 <= 50; cnt2++){
      memset(g, -1, sizeof(g));
      g[0][0][0] =  1;
      for(int i = 0; i < cnt1+cnt2; i++) {
        int du = 1;
        if(i >= cnt1) du = 2;
        for (int one = 0; one <= i; one++) {
          for (int two = 0; one+two <= i; two++) if(g[i][one][two] != -1) {
            for (int w = 0; w <= du; w++) {
              for (int toOne = 0; toOne <= w && toOne <= one; toOne++) {
                int toTwo = w - toOne;
                if(toTwo > two) continue;
                Add(g[i + 1][one-toOne+(du-w==1)+toTwo][two-toTwo+((du-w)==2)], \
                    1LL * g[i][one][two] * bino[one][toOne] % MOD * bino[two][toTwo] % MOD);
              }
            }
          }
        }
      }
      if(~g[cnt1+cnt2][0][0]) {
        c[cnt1][cnt2] = g[cnt1+cnt2][0][0];
      }
    }
  }
  int p[55];
  p[0] = 1;
  for(int i = 1; i <= 50; i++) p[i] = 1LL * p[i-1] * i % MOD;
  for(int one = 0; one <= 50; one++) {
    for(int two = 0; one+two <= 50; two++) {
      for(int k = 1; k <= one + 2*two && k <= 50; k++) {
        int &ret = h[one][two][k];
        bool flag = false;
        for(int toOne = 0; toOne <= one && toOne <= k; toOne++) {
          int toTwo = k - toOne;
          if(toTwo > two * 2) continue;
          for(int x = 0; x <= two && 2*x <= toTwo; x ++) {
            if(x * 2 + two - x < toTwo) continue;
            int mul = 1;
            for(int i = 0; i < x; i++) mul = 1LL * mul * bino[toTwo - 2*i][2]%MOD;
            int a = one - toOne + toTwo - x * 2;
            int b = two - x - (toTwo - x * 2);
            Add(ret, 1LL * c[a][b] * bino[one][toOne] % MOD * bino[k][toOne] % MOD * p[toOne] % MOD * \
                bino[two][x] % MOD * mul % MOD * bino[two - x][toTwo - 2 * x] % MOD * p[toTwo - 2*x] % MOD);
          }
        }
      }
    }
  }
}
int main() {
  init();
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) scanf("%d", &deg[i]);
  memset(dp, -1, sizeof(dp));
  dp[1][1][1] = 1;
  for(int nodes = 1; nodes <= n; nodes++) {
    for(int dep = 1; dep <= nodes; dep++) {
      for(int last = 1; last <= nodes; last++) {// last level has last nodes
        int cnt = dp[nodes][dep][last];
        if(cnt == -1) continue;
        int cnt1 = 0, cnt2 = 0;
        for(int i = nodes-last+1; i <= nodes; i++) {
          if(deg[i] == 3) cnt2++;
          else cnt1++;
        }
        int up = std::min(cnt1+cnt2*2+1, n - nodes);
        for(int now = 1; now <= up; now++) { // enum the new level
          if(nodes == 1) {
            if(now != deg[1]) {
              continue;
            }
          }
          int &ret = dp[nodes + now][dep + 1][now];
          int mul = h[cnt1][cnt2][now];
          if(nodes == 1) mul = 1;
          if(nodes + now == n) { // the end level
            int cnt1 = 0, cnt2 = 0;
            for(int i = n - now + 1; i <= n; i++) {
              if(deg[i] == 3) cnt2++;
              else cnt1 ++;
            }
            mul = 1LL * mul * c[cnt1][cnt2] % MOD;
          }
          Add(ret, 1LL * mul * cnt % MOD);
        }
      }
    }
  }
  int ret = 0;
  for(int dep = 2; dep <= n; dep++) {
    for(int last = 1; last <= n; last++) if(dp[n][dep][last] != -1) {
      Add(ret, dp[n][dep][last]);
    }
  }
  printf("%d\n", ret);
  return 0;
}