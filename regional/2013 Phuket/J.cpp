#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 500050;
long long sum[N];
int c[N * 2];
long long num[N];
int tot;
void update(int x, int y) {
        for(x++; x <= tot; x += x & -x) {
                if(y > c[x]) c[x] = y;
        }
}
int query(int x) {
        x++;
        int mx = -1;
        for(;x; x -= x&-x) {
                if(c[x] > mx) mx = c[x];
        }
        return mx;
}
int main() {
        int T;
        scanf("%d", &T);
        while(T --) {
                int n, x;
                scanf("%d%d",&n,&x);
                int a;
                tot = 0;
                sum[0] = 0;
                for(int i = 1; i <= n; i++) {
                        scanf("%d",&a);
                        sum[i] = sum[i - 1] + a;
                        num[tot++] = sum[i];
                        num[tot++] = sum[i] - x;
                }
                num[tot++] = 0;
                sort(num, num + tot);
           /*     for(int i = 0; i < tot; i++) printf("%lld ",num[i]);
                puts("");
                */
                tot = unique(num, num + tot) - num;
                for(int i = 0; i <= tot; i++) c[i] = -1;
                int id = lower_bound(num, num + tot, 0) - num;
               // printf("id=%d\n",id);
                update(id, 0);
                int ret = -1;
                for(int i = 1; i <= n; i++) {
                        int id = lower_bound(num, num + tot, sum[i] - x) - num;
                        int id2 = lower_bound(num, num + tot, sum[i]) - num;
                 //       printf("id=%d id2=%d\n",id,id2);
                        int tmp = query(id);
                  //      printf("tmp=%d\n",tmp);
                        if(tmp != -1 && (ret == -1 || i - tmp < ret)) {
                                ret = i - tmp;
                        }
                 //       printf("i=%d ret=%d\n",i,ret);
                        update(id2, i);
                }
                printf("%d\n",ret);
        }
        return 0;
}
/*3
5 4
1 2 1 2 1
-3 -1 0 0 1 1 1 2 2 2 3
*/