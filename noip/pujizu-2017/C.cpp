#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int mp[N][N];
int m;

int id(int x, int y) {
    return (x - 1) * m + y;
}

int dist[N * N * 2];
vector <pair<int,int> > e[2 * N * N];
void add_edge(int a, int b, int c) {
    e[a].push_back(make_pair(b, c));
}

int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

void dijkstra(int start) {
    int n = 2 * m * m;
    fill(dist + 1, dist + n + 1, -1);
    dist[start] = 0;
    priority_queue <pair<int, int> > Q;
    Q.push(make_pair(0, start) );
    while (!Q.empty() ) {
        pair<int, int> top = Q.top(); Q.pop();
        int d = -top.first;
        int u = top.second;
        if (d > dist[u]) continue;
        for (auto it : e[u]) {
            if (dist[it.first] == -1 || dist[it.first] > dist[u] + it.second) {
                dist[it.first] = dist[u] + it.second;
                Q.push(make_pair(-dist[it.first], it.first));
            }
        }
    }
    if (mp[m][m] != -1) {
        printf("%d\n", dist[id(m,m)]);
    } else {
        int ret = dist[id(m, m)];
        if (ret == -1) {
            ret = dist[2 * m * m];
        } else if ( dist[2 * m * m] != -1 && dist[2 * m * m] < ret) {
            ret = dist[2 * m * m];
        }
        printf("%d\n", ret);
    }
}

int main()
{
    int n;
    scanf("%d%d", &m, &n);
    int x, y, c;
    memset(mp, -1, sizeof(mp));
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &x, &y, &c);
        mp[x][y] = c;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < 4; k++) {
                int x = i + dir[k][0];
                int y = j + dir[k][1];
                if (x < 1 || x > m || y < 1 || y > m) {
                    continue;
                }
                if (mp[x][y] == -1 && mp[i][j] != -1) {
                    mp[x][y] = 0;
                    add_edge(id(i,j), id(x,y), 2 + (mp[i][j] != mp[x][y]) );
                    mp[x][y] = 1;
                    add_edge(id(i,j), id(x,y) + m * m, 2 + (mp[i][j] != mp[x][y]) );
                    mp[x][y] = -1;
                } 
                if (mp[x][y] != -1 && mp[i][j] != -1) {
                    add_edge(id(i, j), id(x, y) ,mp[i][j] != mp[x][y] );
                }
                if (mp[x][y] != -1 && mp[i][j] == -1) {
                    mp[i][j] = 0;
                    add_edge(id(i, j), id(x,y), (mp[x][y] != mp[i][j]) );
                    mp[i][j] = 1;
                    add_edge(id(i,j) + m * m, id(x,y), mp[x][y] != mp[i][j]);
                    mp[i][j] = -1;
                }
            }
        }
    }
    dijkstra(1);
    return 0;
}
