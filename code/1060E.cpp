#include <bits/stdc++.h>
using namespace std;

const int N = 222222;

vector <int> e[N];

long long ret;
int n;
int son[N];
int dp[N][2];

void dfs(int u, int f) {
	dp[u][0] = 1;
	for (int v: e[u]) {
		if (v != f) {
			dfs(v, u);
			son[u] += son[v];
		}
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
	ret = n - 1;
	dfs(1, 0);
	printf("%lld\n", ret);
	return 0;
}