#include <bits/stdc++.h>
using namespace std;

void checkmin(long long &x, long long y) {
    if (y < x) {
        x = y;
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector <int> p(n), c(n);
    vector <int> cnt(m + 1, 0);
    vector<vector <int> > party(m + 1);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &p[i], &c[i]);
        party[p[i]].push_back(c[i]);
        cnt[p[i]]++;
    }
    for (int i = 1; i <= m; i++) {
        sort(party[i].begin(), party[i].end());
    }
    long long ret = 1LL << 60;
    for (int other = 0; other <= n / 2; other++) {
        long long cost = 0;
        int make = cnt[1];
        multiset<int> st;
        for (int i = 0; i < n; i++) if (p[i] != 1) {
            st.insert(c[i]);
        }
        for (int i = 2; i <= m; i++) {
            if (cnt[i] > other) {
                make += cnt[i] - other;
                for (int j = 0; j < cnt[i] - other; j++) {
                    cost += party[i][j];
                    st.erase(st.find(party[i][j]));
                }
            }
        }
        int round = other - make + 1;
        for (int i = 0; i < round && !st.empty(); i++) {
            cost += *st.begin();
            st.erase(st.begin());
            make++;
        }
        if (make > other) {
            checkmin(ret, cost);
        }
    }
    printf("%lld\n", ret);
    return 0;
}
