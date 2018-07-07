#include <cstdio>
#include <cstring>
#include <algorithm>
int a[110];
int f[110][110];
int mx[110][110];
int mi[110][110];
void Min(int &x, int y) {
        if(x == -1 || y < x) x = y;
}
int main() {
        int T, ca = 1;
        int n,m;
        scanf("%d",&T);
        while(T--) {
                scanf("%d%d", &n,&m);
                for(int i = 1; i <= n; i++) {
                        scanf("%d",&a[i]);
                }
                std::sort(a + 1, a + n + 1);
                memset(f, -1, sizeof(f));
                f[0][0] = 0;
                for(int i = 0; i <= n; i++) {
                        for(int j = 0; j <= i && j <= m; j++) if(f[i][j] != -1){
                                for(int k = i + 1; k <= n; k++) {
                                        Min(f[k][j + 1], f[i][j] + a[k] - a[i + 1]);
                                }
                        }
                }
                printf("Case #%d: %d\n",ca++, f[n][m]);
        }
        return 0;
}

