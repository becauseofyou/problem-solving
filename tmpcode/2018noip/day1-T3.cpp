#include <bits/stdc++.h>
using namespace std;

const int N = 55555;

vector <pair<int, int> > e[N];
int n, m;
int w[N];
int total;

void dfs(int u, int f, int x) {
    if (total >= m) {
        return ;
    }
    multiset <int> st;
    for (auto it : e[u]) {
        if (it.first != f) {
            dfs(it.first, u, x);
            if (total >= m) {
                return ;
            }
            int value = w[it.first] + it.second;
            if (value >= x) {
                total++;
            } else {
                st.insert(value);
            }
        }
    }
    if (total >= m) {
        return ;
    }
    int left = 0;
    while (!st.empty()) {
        auto it = st.begin();
        int value = *it;
        st.erase(it);
        if (*it >= x) {
            total ++;
            continue;
        }

        auto it_pair = st.lower_bound(x - *it);
        if (it_pair == st.end()) {
            left = max(left, value);
        } else {
            total ++;
            st.erase(it_pair);
        }
    }
    w[u] = left;
}

bool judge (int x) {
    total = 0;
    dfs(0, -1, x);
    return total >= m;
}

int main () {
    scanf("%d%d", &n, &m);
    int a, b, c;
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        e[a].push_back(make_pair(b, c));
        e[b].push_back(make_pair(a, c));
    }
    int l = 1, r = 500000000, best = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (judge (mid)) {
            best = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", best);
    return 0;
}
