#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long l, r;
        scanf("%lld%lld", &l, &r);

        long long x = 0;
        long long left = 0, right = 0;
        long long ret = r;
        for (int i = 62; i >= 0; i--) {
            long long a = (1LL<<i) & l;
            long long b = (1LL<<i) & r;
            if(a>0) left = left * 2 + 1;
            else left = left * 2;
            if(b>0) right = right * 2 + 1;
            else right = right * 2;
            if ( b > 0 ) {
                if (x * 2 >= left && x * 2 <= right) {
                    x = x * 2;
                } else {
                    x = x * 2 + 1;
                }
            } else {
                if (x * 2 + 1 >= left && x * 2 + 1 <= right) {
                    ret |= 1LL << i;
                    x = x * 2 + 1;
                } else {
                    x = x * 2;
                }
            }
        }
        printf("%lld\n", ret);
    }
    return 0;
}
