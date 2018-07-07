#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
using namespace std;

#define snuke(it,x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); it ++)
#define pb push_back
#define mp make_pair

const int N = 303000 + 101000*2;
const int INF = 0x3f3f3f3f;
map<string,int> station;
char s[333],ss[333],tt[333];
int ntot,mtot,dis[N],f[N],que[N],qf,qe,deg[N];
vector<pair<int,int> > G[N];

void bfs(int s) {
        for (int i = 0; i < ntot; i ++) {
                dis[i] = -1;
        }
        dis[s] = 0;
        qf = qe = 0;
        que[qe++] = s;
        while (qf!=qe) {
                int u = que[qf++];
                snuke(it,G[u]) {
                        int v = it->first;
                        if (dis[v]==-1) {
                                dis[v] = dis[u]+1;
                                que[qe++] = v;
                        }
                }
        }
}

void work() {
        station.clear();

        // read station name
        ntot = 0;
        scanf("%*s");
        while (true) {
                scanf("%s",s);
                bool mark = false;
                int len = strlen(s);
                if (s[len-1]==',') {
                        s[len-1] = 0;
                } else {
                        mark = true;
                }
                station[s] = ntot ++;
                if (mark) break;
        }
        
        // read line name
        mtot = 0;
        scanf("%*s");
        while (true) {
                scanf("%s",s);
                int len = strlen(s);
                mtot ++;
                if (s[len-1]!=',') break;
        }

        for (int i = 0; i < ntot+mtot*2; i ++) {
                G[i].clear();
        }

        for (int i = 0; i < mtot; i ++) {
                scanf("%*s%*s");
                vector<int> z;
                while (true) {
                        scanf("%s",s);
                        bool mark = false;
                        int len = strlen(s);
                        if (s[len-1]==',') {
                                s[len-1] = 0;
                        } else {
                                mark = true;
                        }
                        z.pb(station[s]);
                        if (mark) break; }
                for (int i = 0; i < (int)z.size(); i ++) {
                        int v = z[i];
                        G[v].pb(mp(ntot,-i));
                        G[ntot].pb(mp(v,i));
                }
                ntot ++;
                reverse(z.begin(),z.end());
                for (int i = 0; i < (int)z.size(); i ++) {
                        int v = z[i];
                        G[v].pb(mp(ntot,-i));
                        G[ntot].pb(mp(v,i));
                }
                ntot ++;
        }

        scanf("%*s%*s%*s%s",ss);
        int _s = station[ss];
        scanf("%*s%*s%*s%s",tt);
        int _t = station[tt];

        bfs(_s);

        for (int i = 0; i < ntot; i ++) {
                deg[i] = 0;
                f[i] = -INF;
        }
        f[_s] = 0;
        for (int i = 0; i < ntot; i ++) {
                snuke(it,G[i]) {
                        int v = it->first;
                        if (dis[v]==dis[i]+1) {
                                deg[v] ++;
                        }
                }
        }

        qf = qe = 0;
        que[qe++] = _s;
        while (qf!=qe) {
                int u = que[qf++];
                snuke(it,G[u]) {
                        int v = it->first;
                        int w = it->second;
                        if (dis[u]+1!=dis[v]) continue;
                        f[v] = max(f[v],f[u]+w);
                        deg[v] --;
                        if (deg[v]==0) {
                                que[qe++] = v;
                        }
                }
        }

        printf("optimal travel from %s to %s:",ss,tt);
        printf(" %d line",dis[_t]/2);
        if (dis[_t]/2>1) {
                putchar('s');
        }
        printf(", %d minute",f[_t]);
        if (f[_t]>1) {
                putchar('s');
        }
        puts("");
}

int main() {
        int cas;
        scanf("%d",&cas);
        while (cas--) {
                work();
        }
        return 0;
}

