#include <bits/stdc++.h>
using namespace std;

const int inf = (int)1e9;
const int MAX_NODE = 100010; // 100000个点
const int MAX_EDGE = 200010;//100000条边，双向边开两倍空间
int head[MAX_NODE], nxt[MAX_EDGE], pnt[MAX_EDGE], weight[MAX_EDGE];
int E;

void add_edge(int a, int b, int c) {
    pnt[E] = b;
    nxt[E] = head[a];
    weight[E] = c;
    head[a] = E++;
}
int d[MAX_NODE];
int dijkstra(int s, int t, int n) {
    priority_queue<pair<int,int> > q;//默认大根堆，如果元素是pair，默认按照第一个关键字排序
    for (int i = 0; i < n; i++) {
        d[i] = inf;
    }
    d[s] = 0;
    q.push(make_pair(-d[s], s));//默认是大根堆,插入相反数就可以当作小根堆
    while(!q.empty()) {
        pair<int,int> now = q.top(); q.pop();
        int dis = -now.first;
        int u = now.second;
        if (dis != d[u]) {// 堆里面拿出来的值不是真实的值
            continue;
        }
        for (int i = head[u]; i != -1; i = nxt[i]) {//u的最短路已经确定，用它来更新邻接点
            if (dis + weight[i] < d[pnt[i]]) {
                d[pnt[i]] = dis + weight[i];
                q.push(make_pair(-d[pnt[i]], pnt[i]));
            }
        }
    }
    return d[t];
}

int main() {
	int n, m, a, b, c;
	while (scanf("%d%d", &n, &m) == 2) {
		if (n == 0 && m == 0) {
			break;
		}
        E = 0;
        memset(head, -1, sizeof(head));
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d",&a,&b,&c);
            a--; b--;
            add_edge(a, b, c);
            add_edge(b, a, c);
		}
		printf("%d\n", dijkstra(0, n - 1, n) );
	}
    return 0;
}
