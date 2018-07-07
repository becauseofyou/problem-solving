#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

#define mp make_pair
#define pb push_back
typedef long long lld;
typedef pair<int,int> PII;
const lld Inf = (lld)1e30;
lld lim;
pair<int,PII> ch[5];
vector<pair<lld,pair<lld,lld> > > eum;

void work() {
        sort(ch,ch+5);
        reverse(ch,ch+5);
        eum.clear();
        for (int i = 0; i <= ch[0].first; i ++) {
                for (int j = 0; j <= ch[1].first; j ++) {
                        lld a = (lld)i*ch[0].second.first + (lld)j*ch[1].second.first;
                        lld b = (lld)i*ch[0].second.second + (lld)j*ch[1].second.second;
                        eum.pb(mp(a,mp(b,a)));
                }
        }
        lld ana = -1,anb = Inf;
        sort(eum.begin(),eum.end());
        for (int i = (int)eum.size()-2; i >= 0; i --) {
                if (eum[i].second.first>eum[i+1].second.first || eum[i].second.first==eum[i+1].second.first 
                                && eum[i].second.second>eum[i+1].second.second) {
                        eum[i].second = eum[i+1].second;
                }
        }
        for (int i = 0; i <= ch[2].first; i ++) {
                for (int j = 0; j <= ch[3].first; j ++) {
                        for (int k = 0; k <= ch[4].first; k ++) {
                                lld a = (lld)i*ch[2].second.first + (lld)j*ch[3].second.first + (lld)k*ch[4].second.first;
                                lld b = (lld)i*ch[2].second.second + (lld)j*ch[3].second.second + (lld)k*ch[4].second.second;
                                vector<pair<lld,pair<lld,lld> > >::iterator it = lower_bound(eum.begin(),eum.end(),mp(lim-a,mp(0ll,0ll)));
                                if (it==eum.end()) continue;
                                a += it->second.second;
                                b += it->second.first;
                                if (b<anb) {
                                        ana = a;
                                        anb = b;
                                } else if (b==anb && a<ana) {
                                        ana = a;
                                        anb = b;
                                }
                        }
                }
        }
        printf("%lld %lld\n",anb,ana);
}

int main() {
        int cas;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%lld",&lim);
                lld total = 0;
                for (int i = 0; i < 5; i ++) {
                        int a,b,c;
                        scanf("%d%d%d",&a,&b,&c);
                        ch[i] = mp(a,mp(b,c));
                        total += (lld)a*b;
                }
                if (total<lim) {
                        puts("We are doomed!!");
                        continue;
                }
                work();
        }
        return 0;
}

