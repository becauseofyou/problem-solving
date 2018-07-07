#include <bits/stdc++.h>
using namespace std;

int main () {
    int T, N, B;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &N, &B);
        if (N < B) {
            puts("0");
            continue;
        }
        int mid = N / 2;
        int mod = mid % B;
        long long x = mid - mod;
        int cnt = 0;
        long long ret = 0;
        for (long long i = max(0LL, x - 2LL * B); i <= N; i += B) {
            if(++cnt > 5) {
                break;
            }
            ret = max(ret, 1LL * (N - i) * i / B);
        }
        printf("%lld\n", ret);
    }
    return 0;
}
