#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

const int N = 377777;

int nxt[9][4] = {{1, 8, 6, 3},{2, 0, 7, 4},{3, 1, 5, 8},{4,2,0,6},{5,3,1,7},{4,6,2,8},{7,5,3,0},{8,6,4,1},{0,7,5,2}};
int f[11];
bool vis[N];
int val[N], vv[11], step[N];

void init() {
        f[0] = 1;
        for(int i = 1;i <= 9; i++)      f[i] = f[i-1]*i;
        memset(val, -1, sizeof(val));
}

int Get(int a[]) {
        int ret = 0;
        for(int i = 0;i < 9; i++)       vv[i] = 0;
        for(int i = 0;i < 9; i++) {
                int cnt = 0;
                for(int j = a[i]-1;j >= 0; j--) if(!vv[j])
                        cnt++;
                ret += cnt*f[9-i-1];
                vv[a[i]] = 1;
        }
        return ret;
}

int GG(int a[]) {
        int ret = 0;
        for(int i = 0;i < 9; i++)       ret = ret*10+a[i];
        return ret;
}
queue<int>      qu;

int a[11], b[11];
void chan(int x) {
        for(int i = 8;i >= 0; i--)      a[i] = x%10, x /= 10;
}
int ch, cv;

int bfs(int s, int go) {
        while(!qu.empty())      qu.pop();
        qu.push(s);
        for(int i = 0;i < N; i++)       step[i] = 1000000000;
        step[s] = 0;
//        printf("%d %d\n", s, go);
        vis[s] = true;
        while(!qu.empty()) {
                int cur = qu.front(); qu.pop();
                vis[cur] = false;
                if(step[cur] >= step[go])       continue;
                chan(val[cur]);
                for(int i = 0;i < 9; i++) if(a[i] == 0) {
                        int now;
                        for(int j = 0;j < 4; j++) {
                                if(j <= 1)      now = ch;
                                else    now = cv;
                                swap(a[i], a[nxt[i][j]]);
                                int cc = Get(a);
                                if(val[cc] == -1) {
                                        val[cc] = GG(a);
                                }
                                if(step[cur]+now < step[cc]) {
                                        step[cc] = step[cur] + now;
                                        if(!vis[cc]) {
                                                vis[cc] = true;
                                                qu.push(cc);
                                        }
                                }
                                swap(a[i], a[nxt[i][j]]);
                        }
                }
        }
        return step[go];
}

int main() {
        init();
        while(scanf("%d%d", &ch, &cv) == 2 && ch) {
                for(int i = 0;i < 9; i++)       scanf("%d", &a[i]);
                int s = Get(a);
                val[s] = GG(a);
                for(int i = 0;i < 9; i++)       scanf("%d", &b[i]);
                int go = Get(b);
                val[go] = GG(a);
                printf("%d\n", bfs(s, go));
        }
        return 0;
}