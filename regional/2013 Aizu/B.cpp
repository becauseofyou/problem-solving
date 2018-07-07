#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

#define mp make_pair
#define pb push_back
typedef pair<int,int> PII;
int n,len,anst,ansd,ansdir;

void modify(int tim,int d,int id) {
        if (tim>anst || tim==anst && d<ansdir) {
                anst = tim;
                ansd = id;
                ansdir = d;
        }
}

void work(vector<pair<PII,int> > &v) {
        int sz = (int)v.size();
        if (sz==0) return ;
        int left = 0;
        for (int i = 0; i < sz; i ++) {
                int d = v[i].first.first;
                left += d==0;
        }
        for (int i = sz-1; i >= 0; i --) {
                int d = v[i].first.first;
                int p = v[i].first.second;
                if (d==0) {
                        modify(p,d,v[left-1].second);
                        break;
                }
        }
        for (int i = 0; i < sz; i ++) {
                int d = v[i].first.first;
                int p = v[i].first.second;
                if (d==1) {
                        modify(len-p,d,v[left].second);
                        break;
                }
        }
}

int main() {
        while (scanf("%d%d",&n,&len)==2) {
                if (n==0 && len==0) break;
                vector<pair<PII,int> > v[2];
                for (int i = 1; i <= n; i ++) {
                        char s[4];
                        int d,p;
                        scanf("%s%d",s,&p);
                        d = s[0]=='R';
                        if (p&1) {
                                v[0].pb(mp(mp(d,p),i));
                        } else {
                                v[1].pb(mp(mp(d,p),i));
                        }
                }
                anst = -123,ansd = -1,ansdir = -1;
                work(v[0]);
                work(v[1]);
                printf("%d %d\n",anst,ansd);
        } 
        return 0;
}