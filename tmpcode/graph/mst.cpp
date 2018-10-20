#include <bits/stdc++.h>
using namespace std;

const int M = 222222;
struct Edge {
    int a, b, c;
    bool operator < (const Edge& cmp) const {
        return c < cmp.c;
    }
    void in() {
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
    }
}e[M];

struct dsu {
    vector<int> p;
    int n;

    dsu(int n) : n(n) {
        p.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }

    int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }

    void unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            p[x] = y;
        }
    }
};

int main() {
    int n, m;
    while(scanf("%d", &n) == 1) {
        if(n == 0) {
            break;
        }
        scanf("%d", &m);
        if (m == 0) {
            printf("0\n");
            continue;
        }
        for (int i = 0; i < m; i++) {
            e[i].in();
        }
        sort(e, e + m);
        dsu st(n);
        int ret = 0;
        for (int i = 0; i < m; i++) {
            int a = e[i].a;
            int b = e[i].b;
            if (st.get(a) != st.get(b)) {
                ret += e[i].c;
                st.unite(a, b);
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
