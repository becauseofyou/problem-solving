#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define zero(x) ((x>0? x:-x)<1e-15)
const int N = 100;
double a[N][N];
double b[N][N];
int g[110][110];
double det(double a[][N],int n) {
    int i, j, k, sign = 0;
    double ret = 1, t;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            b[i][j] = a[i][j];
    for (i = 0; i < n; i++) {
        if (zero(b[i][i])) {
            for (j = i + 1; j < n; j++)
                if (!zero(b[j][i]))
                    break;
            if (j == n)
                return 0;
            for (k = i; k < n; k++)
                swap(b[i][k], b[j][k]);
            sign++;
        }
        ret *= b[i][i];
        for (k = i + 1; k < n; k++)
            b[i][k] /= b[i][i];
        for (j = i + 1; j < n; j++)
            for (k = i + 1; k < n; k++)
                b[j][k] -= b[j][i] * b[i][k];
    }
    if (sign & 1)
        ret = -ret;
    return ret;
}
int d[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
void add_edge(int i, int j) {
        a[i][j]--;
        a[i][i]++;
}
int main() {
        int t, n;
        scanf("%d",&t);
        while(t--) {
                scanf("%d",&n);
                memset(a, 0, sizeof(a));
                for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                                for(int k = 0; k < 8; k++) {
                                        int x = i + d[k][0];
                                        int y = j + d[k][1];
                                        if(x >= 0 && x < n && y >= 0 && y < n) {
                                                add_edge(i * n + j, x * n + y);
                                        }
                                }
                        }
                }
            /*    for(int i = 0; i < n*n; i++) {
                        for(int j = 0; j < n*n; j++) {
                                printf("%.0lf ",a[i][j]);
                        }
                        puts("");
                }*/
                double ans = det(a, n * n -1);
                printf("%.0f\n", ans);
        }
        return 0;
    /* 0 based
     * a[i][i] = degree[i];
     * if(g[i][j]) {
     *     a[i][j]--;
     * }
     * ans = det(a, n - 1);
     */
}