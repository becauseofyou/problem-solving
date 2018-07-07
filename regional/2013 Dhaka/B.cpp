#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    int t, n, cas = 1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        ll cnt0 = 0, cnt1 = 0, cnt2 = 0;
        for(int i = 0;i < n;i ++) {
            int L, B;
            scanf("%d%d", &L, &B);
            if(B%3 == 0)    cnt0 += (ll)(L-1)*(B-1);
            else if(B%3 == 1) {
                cnt1 += (ll)(L-1)*(B-1);
            }
            else {
                L--;
                cnt2 += (ll)(L+1)/2*(B-1);
                cnt1 += (ll)L/2*(B-1);
            }
        }
        //scanf("%lld%lld%lld", &cnt0, &cnt1, &cnt2);
        printf("Case %d: ", cas++);
        if(cnt1 && !cnt2) {
            if(cnt1 <= 2)   puts("Draw");
            else if((2+cnt0)&1) puts("M");
            else    puts("J");
        }
        else if(!cnt1 && cnt2) {
            if(cnt2 <= 2)   puts("Draw");
            else if((2+cnt0)&1) puts("J");
            else    puts("M");
        }
        else if(!cnt1 && !cnt2) {
            if(!cnt0)   puts("Draw");
            else    puts("J");
        }
        else {
            bool win = false;
            bool draw = false;
            ll c1 = cnt1, c2 = cnt2;
            cnt1--;
            if(cnt2 > cnt1) {
                ll cur = cnt0 + 1 + cnt1 + cnt1;
                if(cur&1)   win = true;
            }
            else if(cnt1-1 > cnt2) {
                ll cur = cnt0+1 + cnt2+1 + cnt2;
                if(cur&1)   win = true;
            }
            else    draw = true;
            cnt1 = c1; cnt2 = c2;
            cnt2--;
            if(cnt1 > cnt2) {
                ll cur = cnt0+1+cnt2+cnt2;
                if(cur&1)   win = true;
            }
            else if(cnt2-1 > cnt1) {
                ll cur = cnt0+1+cnt1+1+cnt1;
                if(cur&1)   win = true;
            }
            else    draw = true;
            if(win) puts("M");
            else if(draw)   puts("Draw");
            else    puts("J");
        }
    }
    return 0;
}