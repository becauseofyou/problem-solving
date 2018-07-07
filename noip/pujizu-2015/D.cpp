#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector <int> s(n), a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int mx = 0, id = -1;
    vector <int> suf(n);
    for (int i = n - 1; i >= 0; i--) {
        if (2 * s[i] + a[i] > mx) {
            mx = 2 * s[i] + a[i];
            id = i;
        }
        suf[i] = id;
    }
    long long ret = 0;
    priority_queue <int> q;
    int right_most = -1;
    for (int step = 0; step < n; step++) {
        int pre_max = 0;
        if (!q.empty()) {
            pre_max = q.top();
        }
        int suf_max = 0;
        if (right_most < n - 1) {
            suf_max = 2 * s[suf[right_most + 1]] + a[suf[right_most + 1]];
            if(right_most != -1) {
                suf_max -= 2 * s[right_most];
            }
        }
        if (pre_max > suf_max) {
            ret += pre_max;
            q.pop();
        } else {
            ret += suf_max;
            int new_right = suf[right_most + 1];
            for (int i = right_most + 1; i < new_right; i++) {
                q.push(a[i]);
            }
            right_most = new_right;
        }
        printf("%lld\n", ret);
    }
    return 0;
}
