#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
vector <int> e[N];
int pre[20][N];
bool vis[N];
int dep[N];

void dfs(int u, int fa) {
	pre[0][u] = fa;
	dep[u] = dep[fa] + 1;
	for (int v : e[u]) {
		if (v != fa) {
			dfs(v, u);
		}
	}
}

int main() {
	int n, k, a, b;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n - 1; i++) {
		scanf("%d%d", &a, &b);
		e[a].emplace_back(b);
		e[b].emplace_back(a);
	}
	dfs(n, 0);
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j <= n; j++) {
			pre[i][j] = pre[i - 1][pre[i - 1][j]];
		}
	}
	vis[n] = true; vis[0] = true;
	int sum = 1;
	vector <int> ret;
	for (int i = n - 1; i >= 1; i--) {
		if (vis[i]) {
			continue;
		}
		int now = i;
		for (int j = 19; j >= 0; j--) {
			if(!vis[pre[j][now]]) {
				now = pre[j][now];
			}
		}
		//printf("now=%d i=%d\n", now,i);
		int tot = dep[i] - dep[now] + 1;
		if (n -sum -tot < k) {
			ret.emplace_back(i);
		} else {
			vis[now] = true;
			for (int x = i; x != now; x = pre[0][x]) {
		//		printf("x=%d\n", x);
				vis[x] = true;
			}
			sum += tot;
		}
	}
	for (int i = (int)ret.size() - 1; i >= 0; i--) {
		printf("%d ",ret[i]);
	}
	return 0;
}