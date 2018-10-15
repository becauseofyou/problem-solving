#include <bits/stdc++.h>
using namespace std;

class dsu {
    public:
        vector<int> p;
        int n;
        vector< vector<int> > seq;

        dsu(int n) : n(n) {
            p.resize(n);
            iota(p.begin(), p.end(), 0);
            seq.resize(n);
            for (int i = 0; i < n; i++) {
                seq[i].push_back(i);
            }
        }

        inline int get(int x) {
            return (x == p[x] ? x : (p[x] = get(p[x])));
        }

        inline bool unite(int x, int y) {
            x = get(x);
            y = get(y);
            if (x != y) {
                p[x] = y;
                seq[y].insert(seq[y].end(), seq[x].begin(), seq[x].end());
                return true;
            }
            return false;
        }
};

const int N = 2222;

const double eps = 1e-5;
inline int sgn(double x) { return x < -eps ? -1 : x > eps; }

int x, y, n;
int a[N], b[N];

bool check(double d, int n) {
    int edge[4];
    int tn = n;
    edge[0] = tn++;
    edge[1] = tn++;
    edge[2] = tn++;
    edge[3] = tn++;
    dsu test(tn);
    for (int i = 0; i < n; i++) {
        if (sgn(1.0 * a[i] - d) < 0) {
            test.unite(i, edge[0]);
        }

        if (sgn(1.0 * b[i] - d) < 0) {
            test.unite(i, edge[1]);
        }

        if (sgn(1.0 * x - a[i] - d) < 0) {
            test.unite(i, edge[2]);
        }

        if (sgn(1.0 * y - b[i] - d) < 0) {
            test.unite(i, edge[3]);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dis2 = (a[i] - a[j])*(a[i] - a[j]) + (b[i] - b[j]) * (b[i] - b[j]);
            if (sgn(dis2 - 4 * d * d) < 0) {
                test.unite(i, j);
            }
        }
    }
    if (test.get(edge[0]) == test.get(edge[1]) ) {
        return false;
    }
    if (test.get(edge[0]) == test.get(edge[2]) ) {
        return false;
    }
    if (test.get(edge[1]) == test.get(edge[3]) ) {
        return false;
    }
    if (test.get(edge[2]) == test.get(edge[3]) ) {
        return false;
    }
    return true;

}
int main() {
    freopen("AC.in","r", stdin);
    scanf("%d%d%d", &x, &y, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }
    // cout << check(3, n) << endl;
    // return 0;
    double l = 0, r = 2e6;
    double best = -1;
    while(sgn(fabs(l - r)) > 0) {
        double mid = (l + r) * 0.5;
        if (check(mid, n)) {
            l = mid;
            best = mid;
        } else {
            r = mid;
        }
    }
    printf("%.2f\n", best);
    return 0;
}
