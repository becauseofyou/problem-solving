#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> edge[510];
vector<pair<int, int> > ret;
int fa[510];
int du[510];
bool vis[510];
int cnt[510];
int find(int x) {
        return fa[x] == x ? x : find(fa[x]);
}
vector<int> d;
void dfs(int u, int dep) {
        if(du[u] == 3 && dep != 0) return ;
        vis[u] = true;
        for(int i = 0; i < edge[u].size(); i++) {
                int to = edge[u][i];
                if(!vis[to]) {
                        if(du[to] == 3) {
                                d.push_back(dep + 1);
                        }
                        dfs(to, dep+1);
                }
        }
}
int main() {
        int T, ca = 1;
        scanf("%d", &T);
        while(T--) {
                ret.clear();
                d.clear();
                int n, m, a, b;
                scanf("%d%d", &n, &m);
                memset(du, 0, sizeof(du));
                memset(cnt, 0, sizeof(cnt));
                for(int i = 1; i <= n; i++) {
                        edge[i].clear();
                        fa[i] = i;
                }
                for(int i = 0; i < m; i++) {
                        scanf("%d%d",&a,&b);
                        edge[a].push_back(b);
                        edge[b].push_back(a);
                        du[a]++;
                        du[b]++;
                        int x = find(a) ;
                        int y = find(b) ;
                        if(x != y) {
                                fa[x] = y;
                        }
                }
                for(int i = 1; i <= n; i++) {
                        cnt[du[i]]++;
                }
                if(ca > 1) {
                        puts("");
                }
                printf("Case %d: ", ca++);
                bool connected = true;
                for(int i = 1; i <= n; i++) {
                        if(find(i) != find(1)) {
                                connected = false;
                        }
                }
                if(!connected) {
                        puts("0");
                        continue;
                }
                // 1 2  5 7
                if(cnt[2] == n - 2 && cnt[1] == 2) { 
                        if(n >= 3 && (n - 3) % 2 == 0) {
                                ret.push_back(make_pair(1, (n - 3) / 2));
                        }
                        if(n >= 6 && (n - 6) % 5 == 0) {
                                ret.push_back(make_pair(2, (n - 6) / 5));
                                ret.push_back(make_pair(5, (n - 6) / 5));
                        }
                        if(n >= 4 && (n - 4) % 3 == 0) {
                                ret.push_back(make_pair(7, (n - 4) / 3));
                        }
                }
                // 0
                if(cnt[2] == n) {
                        if(n >= 6 && (n - 6) % 6 == 0) {
                                ret.push_back(make_pair(0, (n - 6) / 6));
                        }
                }
                // 6 9
                if(cnt[1] == 1 && cnt[3] == 1 && cnt[2] == n - 2 && n == m) {
                        queue<int> Q;
                        memset(vis, false, sizeof(vis));
                        for(int i = 1; i <= n; i++) {
                                if(du[i] == 1) {
                                        Q.push(i);
                                        vis[i] = true;
                                }
                        }
                        int tot = 0;
                        while(!Q.empty()) {
                                int fr = Q.front(); Q.pop();
                                tot++;
                                bool flag = false;
                                for(int i = 0; i < edge[fr].size(); i++) {
                                        int to = edge[fr][i];
                                        if(du[to] == 3) {
                                                flag = true;
                                                break;
                                        }
                                        if(!vis[to]) {
                                                vis[to] = true;
                                                Q.push(to);
                                        }
                                }
                                if(flag) {
                                        break;
                                }
                        }
                        if(tot % 2 == 0 && (n - tot - 4) >= 0 && (n - tot - 4) % 4 == 0 && \
                                        (n - tot - 4) / 4 == tot / 2 - 1)  {
                                ret.push_back(make_pair(6, tot / 2 - 1));
                                ret.push_back(make_pair(9, tot / 2 - 1));
                        }
                }
                //3 4
                if(cnt[3] == 1 && cnt[1] == 3 && m == n - 1) {
                        queue<int> Q;
                        int dis[510]; 
                        memset(vis, false, sizeof(vis));
                        for(int i = 1; i <= n; i++) {
                                if(du[i] == 3) {
                                        Q.push(i);
                                        dis[i] = 0;
                                        vis[i] = true;
                                }
                        }
                        vector<int> tmp;
                        while(!Q.empty()) {
                                int fr = Q.front(); Q.pop();
                                for(int i = 0; i < edge[fr].size(); i++) {
                                        int to = edge[fr][i];
                                        if(!vis[to]) {
                                                vis[to] =  true;
                                                dis[to] = dis[fr] + 1;
                                                if(du[to] == 1) {
                                                        tmp.push_back(dis[to]);
                                                }
                                                Q.push(to);
                                        }
                                }
                        }
                        sort(tmp.begin(), tmp.end());
                        if(tmp[0] == tmp[1] && tmp[0] >= 1 && tmp[1] < tmp[2]) {
                                if(tmp[2] % 2 == 0 && tmp[2] / 2 == tmp[0] )
                                ret.push_back(make_pair(4, tmp[0] - 1));
                        }
                        if(tmp[0] < tmp[1] && tmp[1] == tmp[2] && tmp[2] % 2 == 0 && tmp[2] / 2 == tmp[0]) {
                                ret.push_back(make_pair(3, tmp[0] - 1));
                        }
                }
                //8
                if(cnt[3] == 2 && cnt[2] == n - 2) {
                        int start ;
                        for(int i = 1; i <= n; i++) {
                                if(du[i] == 3) {
                                        start = i;
                                        break;
                                }
                        }
                        memset(vis, false, sizeof(vis));
                        dfs(start, 0);
/*                      for(int i = 0; i < d.size(); i++) {
                                printf("%d " ,d[i]);
                        }
                        puts("");
                        */
                        sort(d.begin(), d.end());
                        if(d.size() == 3 && d[1] == d[2] && d[0] < d[1] && d[1] == 3 * d[0]) {
                                ret.push_back(make_pair(8, d[0] - 1));
                        }
                }
                printf("%d\n", ret.size());
                if(ret.size())sort(ret.begin(), ret.end());
                for(int i = 0; i < ret.size(); i++) {
                        printf("%d %d\n", ret[i].first, ret[i].second);
                }
        }
        return 0;
}