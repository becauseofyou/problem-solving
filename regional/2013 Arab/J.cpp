#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
        if(!b) {
                x = 1; y = 0;
                return a;
        }
        ll ret = exgcd(b, a%b, y, x);
        y -= a/b*x;
        return ret;
}

ll gcd(ll a, ll b) {
        return b ? gcd(b, a%b) : a;
}

int main() {
        int t;
        ll n1,f1,d1,n2,f2,d2;
        scanf("%d", &t);
        while(t--) {
                scanf("%lld%lld%lld%lld%lld%lld", &n1,&f1,&d1,&n2,&f2,&d2);
                if(f1 == f2) {
                        ll LCM = d1/gcd(d1, d2)*d2;
                        ll cnt1 = n1-1, cnt2 = n2-1;
                        ll ans = min(cnt1/(LCM/d1), cnt2/(LCM/d2)) + 1;
                        printf("%lld\n", ans);
                        continue;
                }
                ll x, y;
                ll d = exgcd(d1, -d2, x, y);
                ll n = f2-f1;
                if(n%d == 0) {
                //        printf("x = %I64d y = %I64d\n",x, y);
                        x *= n/d;
                        if(d < 0)       d = -d;
                        x = (x%(d2/d) + d2/d)%(d2/d);
                        y = (x*d1-n)/d2;
                        if(y < 0) {
                                ll cnt = (-y + (d1/d)-1)/(d1/d);
                                x -= cnt*(d2/d);
                                y += cnt*(d1/d);
                        }
                        if(x < 0 || y < 0) {
                                puts("0");
                                continue;
                        }
                        ll cnt1 = n1 - x, cnt2 = n2-y;
                        if(cnt1 >= 1 && cnt2 >= 1) {
                                cnt1--; cnt2--;
                                ll L = d1/d*d2;
                                ll ans = min(cnt1/(L/d1), cnt2/(L/d2)) + 1;
                                printf("%lld\n", ans);
                        }
                        else    puts("0");
                }
                else    puts("0");
        }
        return 0;
}

