#include <bits/stdc++.h>
using namespace std;

const int N = 222222;

vector <int> e[N];

long long ret;
int n;
int dp[N][2];
int son[N];
long long oddPair;
long long sum;

void dfs(int u, int f) {
	dp[u][0] = 1;
    dp[u][1] = 0;
    son[u] = 1;
	for (int v: e[u]) {
		if (v != f) {
			dfs(v, u);
            son[u] += son[v];
            oddPair += 1LL * dp[u][0] * dp[v][0];
            oddPair += 1LL * dp[u][1] * dp[v][1];
            dp[u][0] += dp[v][1];
            dp[u][1] += dp[v][0];
		}
	}
    if (f) {
        sum += 1LL * son[u] * (n - son[u]);
    }
}
int main() { 
	scanf("%d", &n);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs(1, 0);
    cout << (sum+oddPair) / 2 << endl;
	return 0;
}
