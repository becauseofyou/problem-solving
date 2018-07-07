#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1010;
int dp[N], sz[N];
vector<int> edge[N];
void dfs(int u, int f) {
  sz[u] = 1;
  int son = 0;
  vector<int> all;
  for(int i = 0; i < edge[u].size(); i++) {
    int v = edge[u][i];
    if(v != f) {
      son++;
      dfs(v, u);
      sz[u] += sz[v];
      all.push_back(sz[v] - dp[v]);
    }
  }
  if(son == 0) {
    dp[u] = 0;
  } else if(son == 1) {
    dp[u] = sz[u] - 1;
  } else {
    int tmp = 0;
    sort(all.begin(), all.end());
    tmp = all.back();
    all.pop_back();
    tmp += all.back();
    dp[u] = sz[u] - 1 - tmp;
  }
}
int main() {
  int t, ca = 1;
  freopen("B-large.in","r",stdin);
  freopen("B-large.out","w",stdout);
  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    int a, b;
    for(int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for(int i = 1; i < n; i++) {
      cin >> a >> b;
      edge[a].push_back(b);
      edge[b].push_back(a);
    }
    int ret = -1;
    for(int i = 1; i <= n; i++) {
      memset(dp, -1, sizeof(dp));
      dfs(i, -1);
      if(ret == -1 || dp[i] < ret) {
        ret = dp[i];
      }
    }
    printf("Case #%d: ",ca++);
    printf("%d\n",ret);
  }
  return 0;
}

