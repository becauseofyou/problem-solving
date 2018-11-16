#include <bits/stdc++.h>
using namespace std;

const int N = 55555;

vector <pair<int, int> > e[N];
int n, m;
int w[N];
int total;
int pnt[N << 1], nxt[N << 1], we[N << 1], head[N], E;

void add(int a, int b, int c) {
    pnt[E] = b;
    we[E] = c;
    nxt[E] = head[a];
    head[a] = E++;
}

void dfs(int u, int f, int x) {
    if (total >= m) {
        return ;
    }
    multiset <int> st;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = pnt[i];
        if (v != f) {
            dfs(v, u, x);
            if (total >= m) {
                return ;
            }
            int value = w[v] + we[i];
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
    E = 0;
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int a, b, c;
    int sum = 0;
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        sum += c;
        a--; b--;
        add(a, b, c);
        add(b, a, c);
    }
    int l = 1, r = sum, best = -1;
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
