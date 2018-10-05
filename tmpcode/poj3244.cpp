#include <bits/stdc++.h>
using namespace std;

const int N = 222222;

struct Point {
    int x, y, v;
    Point (int x=0, int y=0, int v=0): x(x), y(y), v(v) {
    }
    bool operator < (const Point & cmp) const {
        return x < cmp.x;
    }
}p[N];

int main() {
    int n;
    while (scanf ("%d", &n) == 1 && n) {
        vector <int> a;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &x, &y, &z);
            p[i] = Point(x - y, x - z, x);
            a.push_back(x - z);
        }

        sort (a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        for (int i = 0; i < n; i++) {
            p[i].y = lower_bound(a.begin(), a.end(), p[i].y) - a.begin();
        }

        sort (p, p + n);
        for (int i = 0; i < n; i++) {
        }
        
    }
    return 0;
}
