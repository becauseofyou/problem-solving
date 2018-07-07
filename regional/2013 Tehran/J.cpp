#include <cstdio>
#include <cstring>
const int N = 550;
bool vis[N][N];
int x[N * N], y[N * N], tx[N], ty[N];
int p[N][N][4], q[N][N][4];
int tot;
void gao(int tx[], int ty[], int n) {
        tot = 0;
        x[tot] = tx[0];
        y[tot++] = ty[0];
        for(int i = 1; i < n; i++) {
                if(tx[i] == tx[i - 1]) {
                        int d = ty[i] > ty[i - 1] ? 1 : -1;
                        for(int j = ty[i - 1] + d; j != ty[i]; j += d) {
                                x[tot] = tx[i];
                                y[tot] = j;
                                tot++;
                        }
                        x[tot] = tx[i];
                        y[tot++] = ty[i];
                } else {
                        int d = tx[i] > tx[i - 1] ? 1 : -1;
                        for(int j = tx[i - 1] + d; j != tx[i]; j += d) {
                                x[tot] = j;
                                y[tot++] = ty[i];
                        }
                        x[tot] = tx[i];
                        y[tot++] = ty[i];
                }
        }
}
int main() {
        int n, k;
        while(scanf("%d%d",&n, &k) == 2) {
                if(n == 0 && k == 0) {
                        break;
                }
                memset(p, 0, sizeof(p));
                memset(q, 0, sizeof(q));
                memset(vis, false, sizeof(vis));
                for(int i = 0; i < n; i++) {
                        scanf("%d%d",&tx[i],&ty[i]);
                }
                tx[n] = tx[0];
                ty[n++] = ty[0];
                gao(tx, ty, n);
                for(int i = 0; i < tot; i++) {
                        if(i) {
                                if(x[i] == x[i - 1]) {
                                        int d = y[i] < y[i - 1];
                                        p[x[i]][y[i]][d] = 1;
                                        p[x[i - 1]][y[i - 1]][1 - d] = 1;
                                } else {
                                        int d = x[i] < x[i - 1] ;
                                        q[x[i]][y[i]][d] = 1;
                                        q[x[i - 1]][y[i - 1]][1 - d] = 1;
                                }
                        }
                        if(i == tot - 1) {
                                if(x[i] == x[0]) {
                                        int d = y[i] < y[0] ;
                                        p[x[i]][y[i]][d] = 1;
                                        p[x[0]][y[0]][1 - d] = 1;
                                } else {
                                        int d = x[i] < x[0] ;
                                        q[x[i]][y[i]][d] = 1;
                                        q[x[0]][y[0]][1 - d] = 1;
                                }
                        }
                }
                /*
                   for(int i = 0; i <= 500; i++) {
                   for(int j = 0; j <= 500; j++) {
                   for(int k = 0; k < 2; k++) {
                   if(q[i][j][k]) {
                   printf("%d %d %d\n", i, j, k);
                   }
                   }
                   }
                   }
                   */
                for(int i = 0; i < k; i++) {
                        scanf("%d%d", &tx[i], &ty[i]);
                }
                gao(tx, ty, k);
      //          printf("tot=%d\n", tot);
                for(int i = 0; i < tot; i++) {
              //          printf("xx %d %d\n", x[i], y[i]);
                        if(i) {
                                if(x[i] == x[i - 1]) {
                                        int d = (y[i] - y[i - 1]) < 0;
                                        int tx = x[i];
                                        if(d == 0) {
                                                vis[tx][y[i]] = true;
                                        } else {
                                                vis[tx][y[i - 1]] = true;
                                        }
                                        tx++;
                                        while(tx <= 500  && !p[tx][y[i]][d]) {
                                                if(d == 0) {
                                                        vis[tx][y[i]] = true;
               //                                         printf("dd %d %d\n", tx, y[i]);
                                                }
                                                else {
                                                        vis[tx][y[i - 1]] = true;
                //                                        printf("dd %d %d\n", tx, y[i - 1]);
                                                }
                                                tx++;
                                        }
                                    //    printf("i=%d %d\n",i,x[i]);
                                        tx = x[i];
                                        if(tx == 0) continue;
                                        if(d == 0) {
                                                vis[tx - 1][y[i]] = true;
                                        } else {
                                                vis[tx - 1][y[i - 1]] = true;
                                        }
                                        tx--;
                                        while(tx >= 1 && !p[tx][y[i]][d]) {
                                                if(d == 0) {
                                                        vis[tx - 1][y[i]] = true;
                 //                                       printf("ff %d %d\n", tx-1, y[i]);
                                                }
                                                else{
                                                        vis[tx - 1][y[i - 1]] = true;
                  //                                      printf("ff %d %d\n",tx-1,y[i - 1]);
                                                }
                                                tx--;
                                        }
                                } else {
                                        int d = (x[i] - x[i - 1]) < 0;
                                        int ty = y[i];
                                        if(d == 1) {
                                                vis[x[i]] [ty + 1] = true;
                                        } else {
                                            if(x[i] >= 1)    vis[x[i] - 1][ty + 1] = true;
                                        }
                                        ty++;
                                        while(ty <= 500 && !q[x[i]][ty][d]) {
                                                if(d == 1) vis[x[i]][ty + 1] = true;
                                                else {
                                                        if(x[i] >= 1)
                                                        vis[x[i] - 1][ty + 1] = true;
                                                }
                                                ty++;
                                        }
                                        ty = y[i];
                                        if(d == 1) {
                                                vis[x[i]][ty] = true;
                                        } else {
                                                if(x[i] >= 1)
                                                vis[x[i] - 1][ty] = true;
                                        }
                                        ty--;
                                        while(ty >= 1 && !q[x[i]][ty][d]) {
                                                if(d == 1) vis[x[i]][ty] = true;
                                                else{
                                                        if(x[i] >= 1)
                                                        vis[x[i] - 1][ty] = true;
                                                }
                                                ty--;
                                        }
                                }
                        }
                }
                int ret = 0;
                for(int i = 1; i <= 500; i++) {
                        int cnt = 0;
                        for(int j = 0; j <= 500; j++) {
                                if(p[j][i - 1][1]) {
                                        cnt++;
                                }
                                if(cnt & 1) {
                                        if(vis[j][i]) {
                                                ret++;
                                        }
                                }
                        }
                }
                printf("%d\n", ret);
        }
        return  0;
}