#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

int dsu[222];
int Find(int x) {
        return x==dsu[x] ? x : dsu[x] = Find(dsu[x]);
}

int main() {
        int cas,ca = 0,n,m,K;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d%d%d",&n,&m,&K);
                vector<pair<int,pair<int,int> > > edge;
                for (int i = 0; i <= n; i ++) { dsu[i] = i; }
                for (int i = 0; i < K; i ++) {
                        int x;
                        scanf("%d",&x); x --;
                        edge.push_back(make_pair(0,make_pair(x,n)));
                }
                for (int i = 0; i < m; i ++) {
                        int a,b,c;
                        scanf("%d%d%d",&a,&b,&c); a --; b --;
                        edge.push_back(make_pair(c,make_pair(a,b)));
                }
                sort(edge.begin(),edge.end());
                int ans = 0;
                for (int i = 0; i < (int)edge.size(); i ++) {
                        int a = edge[i].second.first;
                        int b = edge[i].second.second;
                        int w = edge[i].first;
                        a = Find(a);
                        b = Find(b);
                        if (a==b) continue;
                        dsu[a] = b;
                        ans += w;
                }
                printf("Case #%d: %d\n",++ca,ans);
        }
        return 0;
}