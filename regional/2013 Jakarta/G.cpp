#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long lld;
const lld Inf = (lld)1e30;

priority_queue<lld> que[101];

int main() {
        int cas,ca = 0,n;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d",&n);
                for (int i = 0; i < 101; i ++) {
                        while (!que[i].empty()) que[i].pop();
                }
                printf("Case #%d:\n",++ca);
                while (n--) {
                        char s[13];
                        lld s0,t0,r,t;
                        scanf("%s",s);
                        if (s[0]=='P') {
                                scanf("%lld%lld%lld",&t0,&s0,&r);
                                s0 -= t0*r;
                                que[r].push(s0);
                        } else {
                                scanf("%lld",&t);
                                int p = -1;
                                lld mx = -Inf;
                                for (int i = 0; i < 101; i ++) {
                                        if (que[i].empty()) continue;
                                        lld val = que[i].top();
                                        val += t*i;
                                        if (val>=mx) {
                                                mx = val;
                                                p = i;
                                        }
                                }
                                que[p].pop();
                                printf("%lld %d\n",mx,p);
                        }
                }
        }
        return 0;
}

