#include <bits/stdc++.h>
using namespace std;

const int N = 222222;

vector <int> e[N];

long long ret;
int n;
int son[N], cnt[2];

void dfs(int u, int f, int d) {
    cnt[d]++;
    son[u] = 1;
	for (int v: e[u]) {
		if (v != f) {
			dfs(v, u, d ^ 1);
            son[u] += son[v];
		}
	}
    if (f) {
        ret += 1LL * son[u] * (n - son[u]);
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
	dfs(1, 0, 0);
    cout << (ret + 1LL * cnt[0] * cnt[1]) / 2 << endl;
	return 0;
}