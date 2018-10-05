#include <bits/stdc++.h>
using namespace std;

const int dx[] = {1,0,-1,0};
const int dy[] = {0,1,0,-1};

bool vis[10][10];
char mp[10][10];
int ret;
int n, m;


void dfs(int x, int y) {
    if (x == n - 1 && y == m - 1) {
        ret++;
        return ;
    }

    for (int i = 0; i < 4; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (tx < 0 || tx >= n || ty < 0 || ty >= m) {
            continue;
        }
             vis[tx][ty] = true;
        dfs(tx, ty);
        vis[tx][ty] = false; //»ØËÝ ³·Ïú
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", mp[i]);
    }
    dfs(0, 0);
    printf("%d\n", ret);
    return 0;
}

