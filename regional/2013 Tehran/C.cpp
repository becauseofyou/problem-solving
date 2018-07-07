#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

#define snuke(it,x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); it ++)

const int N = 10100;
vector<int> G[N];
int n,m,mark[N],dp[N][2][2];

void toMax(int &a,int b) { if (a<b) a = b; }

void dfs(int u) {
        snuke(it,G[u]) {
                int v = *it;
                dfs(v);
                int tmp[2][2] = {0};
                for (int i = 0; i < 2; i ++) {
                        for (int j = 0; j < 2; j ++) {
                                tmp[i][j] = dp[u][i][j];
                        }
                }
                for (int i = 0; i < 2; i ++) {
                        for (int j = 0; j < 2; j ++) {
                                for (int k = 0; k < 2; k ++) {
                                        for (int r = 0; r < 2; r ++) {
                                                int val = dp[u][i][j]+dp[v][k][r];
                                                if (i==0 && r==0 && mark[v]) {
                                                        toMax(tmp[1][j],val+1);
                                                }
                                                if (j==0 && k==0 && mark[u]) {
                                                        toMax(tmp[i][1],val+1);
                                                }
                                                toMax(tmp[i][j],val);
                                        }
                                }
                        }
                }
                for (int i = 0; i < 2; i ++) {
                        for (int j = 0; j < 2; j ++) {
                                dp[u][i][j] = tmp[i][j];
                        }
                }
        }
}

int main() {
        while (scanf("%d%d",&n,&m)==2 && n) {
                for (int i = 0; i <= n; i ++) {
                        G[i].clear();
                        for (int j = 0; j < 2; j ++) {
                                for (int k = 0; k < 2; k ++) {
                                        dp[i][j][k] = 0;
                                }
                        }
                        mark[i] = 0;
                }
                for (int i = 1; i <= n; i ++) {
                        int x;
                        scanf("%d",&x);
                        G[x].push_back(i);
                }
                for (int i = 0; i < m; i ++) {
                        int x;
                        scanf("%d",&x);
                        mark[x] = 1;
                }
                int ans = 0;
                snuke(it,G[0]) {
                        dfs(*it);
                        int mx = 0;
                        for (int i = 0; i < 2; i ++) {
                                for (int j = 0; j < 2; j ++) {
                                        mx = max(dp[*it][i][j],mx);
                                }
                        }
                        ans += mx;
                }
                printf("%d\n",ans);
        }
        return 0;
}