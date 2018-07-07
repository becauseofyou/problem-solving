#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

vector <int> e[N];
int son[N];

void dfs(int u, int fa) {
	son[u] = 1;
	for (int v : e[u]) {
		if (v != fa) {
			dfs(v, u);
			son[u] += son[v];
		}
	}
}

int main() {
	int n, x, y, a, b;
	scanf("%d%d%d", &n, &x, &y);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs(x, -1);
	int A = son[y];
	memset(son, 0, sizeof(son));
	dfs(y, -1);
	int B = son[x];
	cout << 1LL * n * (n - 1) - 1LL * A * B << endl;
	return 0;
}