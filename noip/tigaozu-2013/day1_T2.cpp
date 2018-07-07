#include <bits/stdc++.h>
using namespace std;

const int md = 99999997;


int ret;
void merge_sort(int l, int r, vector <long long> &a) {
    if (l + 1 == r) {
        return ;
    }
    int m = l + r >> 1;
    merge_sort(l, m, a);
    merge_sort(m, r, a);
    int pt = l;
    for (int i = m; i < r; i++) {
        while (pt < m && a[pt] < a[i]) {
            pt++;
        }
        ret += m - pt;
        if (ret >= md) ret -= md;
    }
    inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r);
}

int inverse_number(vector <long long> &a) {
    merge_sort(0, (int)a.size(), a);
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    vector <long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }
    vector <long long> c = a;
    sort(c.begin(), c.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
    }

    {
        vector <long long> c = b;
        sort(c.begin(), c.end());
        for (int i = 0; i < n; i++) {
            b[i] = lower_bound(c.begin(), c.end(), b[i]) - c.begin();
        }
    }

    vector <int> mp(n);
    for (int i = 0; i < n; i++) {
        mp[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        b[i] = mp[b[i]];
    }
    printf("%d\n", inverse_number(b));
    return 0;
}
