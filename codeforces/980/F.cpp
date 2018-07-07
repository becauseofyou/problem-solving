#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

#define all(x) x.begin(),x.end()
vector <int> e[N];
int bcircle[N];
vector <int> circle[N];
int up[N], down[N];
int n;
bool vis[N];
int pre[N];
int num_circle;
int f[N];

struct node{
	int max_value, max_which;
	int sec_value, sec_which;
	node() {
		max_value = max_which = 0;
		sec_value = sec_which = 0;
	}
	void change_max(int value, int which) {
		sec_value = max_value;
		sec_which = max_which;
		max_value = value;
		max_which = which;
	}
	void change_sec(int value, int which) {
		sec_value = value;
		sec_which = which;
	}
}dp[N];


int mx1[N << 2], mx2[N << 2];
int w[N], top[N];

void pushup(int x) {
	mx1[x] = max(mx1[x + x], mx1[x + x + 1]);
	mx2[x] = max(mx2[x + x], mx2[x + x + 1]);
}

void build(int l, int r, int x) {
	if (l == r) {
		mx1[x] = w[l] - l;
		mx2[x] = w[l] + r;
		return ;
	}
	if (l != r) {
		int m = (l + r) >> 1;
		build(l, m, x + x);
		build(m + 1, r, x + x + 1);
		pushup(x);
	}
}

void update(pair<int,int> &ret, pair<int,int> tmp) {
	if (tmp.first > ret.first) {
		ret.first = tmp.first;
	}
	if (tmp.second > ret.second) {
		ret.second = tmp.second;
	}
}

pair<int,int> query(int L, int R, int l, int r, int x) {
	if (L > R) {
		return make_pair(-n, -n);
	}
	if (L <= l && r <= R) {
		return make_pair(mx1[x], mx2[x]);
	}
	pair<int,int> ret = make_pair(-n, -n);
	int m = (l + r) >> 1;
	if (L <= m) {
		pair<int,int> tmp = query(L, R, l, m, x + x);
		update(ret, tmp);
	}
	if (R > m) {
		pair<int, int> tmp = query(L, R, m + 1, r, x + x + 1);
		update(ret, tmp);
	}
	return ret;
}

void init() {
	dp[0].max_value = -1;
	memset(top, -1, sizeof(top));
	memset(bcircle, -1, sizeof(bcircle));
}

void update(int u, int value, int v) {
	if (value >= dp[u].max_value) {
		dp[u].change_max(value, v);
	} else if (value > dp[u].sec_value) {
		dp[u].change_sec(value, v);
	}
}

void solve_circle(int id) {
	int sz = (int) circle[id].size();
	for (int i = 0; i < sz; i++) {
		w[i] = dp[circle[id][i]].max_value;
	}
	build(0, sz - 1, 1);
	for (int i = 0; i < sz; i++) {

		int k = (i + (sz + 1) / 2) % sz;

	 // cout << "seg" <<" " << k << " " << i << endl;

		if (k > i) {

			pair<int,int> ret1 = query(i + 1, k - 1, 0, sz - 1, 1);
			pair<int,int> ret2 = query(0, i - 1, 0, sz - 1, 1);
			pair<int,int> ret3 = query(k, sz - 1, 0, sz - 1, 1);
			int tmp = max(ret1.second - i, ret2.first + i);
			tmp = max(tmp, ret3.first + i + sz);
			update(circle[id][i], tmp, -1);
		} else {

			pair<int,int> ret1 = query(k, i - 1, 0, sz - 1, 1);
			pair<int,int> ret2 = query(i + 1, sz - 1, 0, sz - 1, 1);

			pair<int,int> ret3 = query(0, k - 1, 0, sz - 1, 1);
			int tmp = max(ret1.first + i, ret2.second - i);
			tmp = max(tmp, sz - i + ret3.second);
			update(circle[id][i], tmp, -1);
		}
	}
}




int dep[N];
void find_circle(int u, int fa) {
				// cout << "u=" << u << endl;
	vis[u] = true;
	pre[u] = fa;
	dep[u] = dep[fa] + 1;
	for (int v : e[u]) {
		if (!vis[v]) {
			find_circle(v, u);
		} else if(v != fa && dep[v] < dep[u]) {
			// cout << "v = " << v << endl;
			top[v] = 1;
			int x = u;
			num_circle++;
			do {
				bcircle[x] = num_circle;
				circle[num_circle].emplace_back(x);
				x = pre[x];
			}while(x != pre[v]);
			reverse(all(circle[num_circle]));
		}
	}
}

// dp[i] 如果i是环上的点就表示不走环边的最长和次长 非环上的点就表示子树的答案
// f[] 环上最高点的子树答案
void dp_down(int u, int fa) {
	vis[u] = true;
	for (int v : e[u]) {
		if (!vis[v]) {
			dp_down(v, u);
			if(bcircle[v] == -1 || top[v] != -1) {
				update(u, f[v] + 1, v);
			} 
		}
	}
	f[u] = dp[u].max_value;
	if (top[u] != -1) { // 环上最高点
		//求f[u]
		f[u] = dp[u].max_value;
		int id = bcircle[u];
		int sz = (int) circle[id].size();
		int tmp = 0;
		for (int i = 1; i < (sz + 1) / 2; i++) {
			tmp = max(tmp, i + dp[circle[id][i]].max_value);
		}
		for (int i = (sz + 1) / 2; i < sz; i++) {
			tmp = max(tmp, sz - i + dp[circle[id][i]].max_value);
		}
		f[u] = max(f[u], tmp);
	}
}


void dp_up(int u, int fa) {
	if (bcircle[u] == -1 || top[u] != -1) { //不是环上的点 或者 是环上最高点
		if (dp[fa].max_which != u ) {
			update(u, dp[fa].max_value + 1, fa);
		} else {
			update(u, dp[fa].sec_value + 1, fa);
		}
		
	}
	if (top[u] != -1) {//一口气处理环上所有的点的答案
		solve_circle(bcircle[u]);
		//cout << "top=" << u << endl;
		int id = bcircle[u];
		// for (int i = 0; i < circle[id].size(); i++) {
		// 	printf("%d %d\n", circle[id][i], dp[circle[id][i]].max_value);
		// }
	}
//	cout << u << endl;
	vis[u] = true;
	for (int v : e[u]) {
		if (!vis[v]) {
			dp_up(v, u);
		}
	}
}

void input() {
	int a, b, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &a, &b);
		e[a].emplace_back(b);
		e[b].emplace_back(a);
	}
}

void output() {
	for (int i = 1; i <= n; i++) {
		printf("%d ", dp[i].max_value);
	}
}

int main() {
	init();
	input();
	
	find_circle(1, 0);
	// for (int i = 1; i <= num_circle; i++) {
	// 	cout << "circle " << i << ":" ;
	// 	for (int v : circle[i]) {
	// 		cout << v << " " ;
	// 	}
	// 	cout << endl;
	// }
	memset(vis, false, sizeof(vis));
	dp_down(1, 0);
	// for (int i = 1; i <= n; i++) {
	// 	printf("dp[%d]=%d %d\n", i, dp[i].max_value, dp[i].sec_value);	
	// }
	memset(vis, false, sizeof(vis));
	//puts("debug");

	dp_up(1, 0);


	output();
	return 0;
}