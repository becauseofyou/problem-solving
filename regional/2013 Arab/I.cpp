#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 1000+5;
int a[N][N], sum[N][N];

int main() {
        int t, n, m;
        scanf("%d", &t);
        while(t--) {
                scanf("%d%d", &n, &m);
                for(int i = 1;i <= n; i++)
                        for(int j = 1;j <= m; j++)
                                scanf("%d", &a[i][j]);
                ll ans = -1000000000000000LL;
                for(int i = n;i >= 1; i--) {
                        for(int j = m;j >= 1; j--) {
                                if(i == n && j == m)    sum[i][j] = a[i][j];
                                else if(i == n) sum[i][j] = sum[i][j+1] + a[i][j];
                                else if(j == m) sum[i][j] = sum[i+1][j] + a[i][j];
                                else    sum[i][j] = (ll)sum[i][j+1] + sum[i+1][j] - sum[i+1][j+1] + a[i][j];
                                ans = max(ans, (ll)sum[i][j]);
                        }
                }
                printf("%lld\n", ans);
        }
        return 0;
}