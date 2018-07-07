#include <bits/stdc++.h>
 
#define DB double 
#define op operator
const DB eps = 1e-8;

int sgn(DB x) {
        return x < -eps ? -1 : x > eps;
}
 
struct PT {
    DB x, y;
    DB dot(const PT &a) {
        return x * a.x + y * a.y;
    }
    PT(DB x = 0, DB y = 0) : x(x), y(y) {
    }
    void in() {
        scanf("%lf%lf", &x, &y);
    }
    bool op == (const PT &a) const {
        return sgn(x - a.x) == 0 && sgn(y - a.y) == 0;
    }
    bool op < (const PT &a) const {
        return sgn(x - a.x) < 0 || sgn(x - a.x) == 0 && sgn(y - a.y) < 0;
    }
    PT op + (const PT &a) const {
        return PT(x + a.x, y + a.y);
    }
    PT op - (const PT &a) const {
        return PT(x - a.x, y - a.y);
    }
    DB op * (const PT &a) const {
        return x * a.y - y * a.x;
    }
    DB length() {
        return sqrt (x*x + y*y);
    }
    void print () {
        printf("%lf %lf\n", x, y);
    }
}p[100010];

bool cmp_y (const PT& a, const PT& b) {
    return sgn(a.y - b.y) < 0;
}

DB closest_pair(PT *p, int n) {
    if (n == 1) {
        return std::numeric_limits<DB>::max();
    }
    int m = n / 2;
    DB x = p[m].x;
    DB d = std::min(closest_pair(p, m), closest_pair(p + m, n - m));
    std::inplace_merge (p, p + m, p + n, cmp_y);
    std::deque <PT> pts;
    for (int i = 0; i < n; i++) {
        if ((fabs(p[i].x - x) - d) >= 0) {
            continue;
        }
        for (int j = 0; j < (int)pts.size(); j++) {
            DB dis = (p[i] - pts[(int)pts.size() - j - 1]).length();
            if (sgn(dis - d) >= 0) {
                break;
            } else {
                d = dis;
            }
        }
        pts.push_back(p[i]);
        if (pts.size() > 6) {
            pts.pop_front();
        }
    }
    return d;
}

int main () {
    int n;
    while (scanf("%d", &n) , n) {
        for (int i = 0; i < n; i++) {
            p[i].in();
        }
        std::sort (p, p + n);
        printf("%.2f\n", closest_pair(p, n) / 2);
    }
    return 0;
}

