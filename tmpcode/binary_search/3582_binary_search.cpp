#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int sum[N], a[N];

int get_interval(int i, int j) {
    return sum[j] - sum[i - 1];
}

int main() {
    int n, S;
    scanf("%d%d", &n, &S);
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    int ret = n;
    for (int left = 1; left <= n; left ++) {
        int l = left, r = n, best = -1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (get_interval(left, m) >= S) {
                best = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        if (best != -1) {
            if (best - left + 1 < ret) {
                ret = best - left + 1;
            }
        }
    }
    printf("%d\n", ret);
    return 0;
}
