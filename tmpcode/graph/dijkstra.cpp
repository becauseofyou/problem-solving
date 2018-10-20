#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int inf = (int)1e9; // 根据具体题目而定

int d[N];
bool vis[N];
int mp[N][N];

int dijkstra(int s, int t, int n) { //s为起点,t为终点, n为点数，mp数组为图的邻接矩阵
    for(int i = 0; i < n; i++) {
        d[i] = inf; 
        vis[i] = false;
    }
    d[s] = 0; 
    for (int step = 0; step < n; step++) { //每次都会找一个点确定它的最短路
        int id = -1;
        int mi = inf;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && d[i] < mi) {//寻找未访问的点中d值最小的点
                mi = d[i];
                id = i;
            }
        }
        if (id == -1) {//可能会出现找不到的情况，图不连通
            break;
        }
        vis[id] = true;//标记id这个点已经确定了最短路，以后不需要再理
        for (int i = 0; i < n; i++) {
            if (mp[id][i] != -1 && d[id] + mp[id][i] < d[i]) { //注意判断边是否存在
                d[i] = d[id] + mp[id][i];
            }
        }
    }
    return d[t];
}

int main()
{
	int n, m, a, b, c;
	while (scanf("%d%d", &n, &m) == 2) {
		if (n == 0 && m == 0) {
			break;
		}
		memset(mp, -1, sizeof(mp));//一开始设为-1表示一条边都不存在
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d",&a,&b,&c);
			a--;
			b--;
			mp[a][b] = mp[b][a] = c;
		}
		printf("%d\n", dijkstra(0, n - 1, n) );
	}
	return 0;
}
