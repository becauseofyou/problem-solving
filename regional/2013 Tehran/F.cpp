#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 50000+5;
const double eps = 1e-8;
struct PP {
    int r, a, b;
    bool operator < (const PP& a)const {
        return b < a.b;
    }
}q[N];
int n, st[N];

bool ok(double mid) {
    //printf("mid = %f\n", mid);
    double pre = mid*q[1].a + q[1].b;
    for(int i = 2;i <= n; i++) {
        double cur = mid*q[i].a + q[i].b;
        if(cur < pre)   return false;
        pre = cur;
    }
    int top = 0;
    st[++top] = 1;
    for(int i = 2;i <= n; i++) {
        while(top > 0 && q[st[top]].r < q[i].r) {
            double dis = (mid*q[i].a+q[i].b) - (mid*q[st[top]].a+q[st[top]].b);
          //  printf("i = %d top = %d dis = %f %f\n", i, st[top], dis, 2.0*sqrt(1.0*q[i].r)*sqrt(1.0*q[st[top]].r));
            if(dis <= 2.0*sqrt(1.0*q[i].r)*sqrt(1.0*q[st[top]].r))  return false;
            top--;
        }
        if(top) {
            double dis = (mid*q[i].a+q[i].b) - (mid*q[st[top]].a+q[st[top]].b);
            if(dis <= 2.0*sqrt(1.0*q[i].r)*sqrt(1.0*q[st[top]].r))  return false;
        }
        //for(int j = 1;j <= top; j++)    printf("%d ", st[j]);puts("");
        st[++top] = i;
    }
    return true;
}

int main() {
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 1;i <= n; i++) {
            scanf("%d%d%d", &q[i].r, &q[i].a, &q[i].b);
        }
        sort(q+1, q+n+1);
        bool flag = false;
        double ans;
        double l = 0, r = 1e10;
        while(r-l > eps) {
            double mid = (l+r)/2;
            if(!ok(mid)) {
                flag = true;
                ans = mid;
                r = mid;
            }
            else    l = mid;
        }
        if(flag)    printf("%.2f\n", ans);
        else    puts("Collision-Free System");
    }
    return 0;
}