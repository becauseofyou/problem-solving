#include <cstdio>
#include <queue>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
using std::vector;
using std::set;
using std::queue;
const int MAX_NODE = 5010;
const int MAX_EDGE = 100010;
int g[MAX_NODE][MAX_NODE];
int in[MAX_EDGE][2];
vector<int> weights;
set<int> st[MAX_NODE];
bool vis[MAX_NODE];
int pt;
void bfs(int s) {
	memset(vis, false, sizeof(vis));
	queue<int> Q;
	Q.push(s);
	vis[s] = true;
	pt = 0;
	while(!Q.empty()) {
		int fr = Q.front(); Q.pop();
		for(set<int> ::iterator it = st[fr].begin(); it != st[fr].end(); it++) {
			if(vis[*it]) {
				continue;
			}
			vis[*it] = true;
			g[fr][*it] = g[*it][fr] = weights[pt++];
			Q.push(*it);
		}
	}
}
int main() {
	int t, ca = 1, a, b, c, source, n, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &m, &source);
		for(int i = 1; i <= n; i++) {
			st[i].clear();
		}
		weights.clear();
		memset(g, -1, sizeof(g));
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &a, &b, &c);
			in[i][0] = a;
			in[i][1] = b;
			weights.push_back(c);
			st[a].insert(b);
			st[b].insert(a);
		}
		std::sort(weights.begin(), weights.end());
		bfs(source);
		printf("Case %d:\n", ca++);
		for(int i = 0; i < m; i++) {
			int a = in[i][0];
			int b = in[i][1];
			if(g[a][b] == -1) {
				printf("%d %d %d\n", a, b, weights[pt++]);
			} else {
				printf("%d %d %d\n", a, b, g[a][b]);
			}
		}
	}
	return 0;
}