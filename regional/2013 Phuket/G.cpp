#include <cstdio>
#include <algorithm>
using std::sort;
using std::fill;
struct Point {
        int x, y;
        Point(int x = 0, int y = 0) : x(x), y(y)  {
        }
        bool operator < (const Point &cmp) const {
                return x < cmp.x || (x == cmp.x && y < cmp.y);
        }
}p[55];
int dp[55];
int main() {
        int t;
        scanf("%d",&t);
        while(t--) {
                int a, b;
                int tot = 0;
                while(scanf("%d%d",&a,&b), (a + b)) {
                        p[tot] = Point(a, b);
                        tot ++;
                }
                sort(p, p + tot);
                fill(dp, dp + tot, 1);
                int mx = 1;
                for(int i = 0; i < tot; i++) {
                        for(int j = i + 1; j < tot; j++) {
                                if(p[i].y <= p[j].x) {
                                        if(dp[i] + 1 > dp[j]) {
                                                dp[j] = dp[i] + 1;
                                                if(dp[j] > mx) {
                                                        mx = dp[j];
                                                }
                                        }
                                }
                        }
                }
                printf("%d\n",mx);
        }
        return 0;
}

