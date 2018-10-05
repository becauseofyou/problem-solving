#include <bits/stdc++.h>
using namespace std;

/*
   0 1 2
   010
   020
   210
   120
   f[3][0] -> f[4][1]
           -> f[4][2]


   f[N][3]:  f[i][j] 第 i个位置 为j的方案数
   1 0 0
   0 1 1
   2 1 1


   */
long long f[55][3];
int main () {
/*
    f[1][0] = 1;
    for (int i = 2; i <= 50; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) if (k != j){
                f[i][j] += f[i - 1][k];
            }
        }
    }
    int n;
    scanf("%d", &n);

    long long ret = 0;
    ret = (f[n][1] + f[n][2]) * 3;
    printf("%lld\n", ret);
*/
    return 0;
}
