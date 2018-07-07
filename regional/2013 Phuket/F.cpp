#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

typedef long long lld;
const int MOD = 10007;
const int N = 1010;
int n,W,cnt[N],C[N][N],dp[2][210][N<<1],pre[N];

void init() {
        for (int i = 0; i < N; i ++) {
                C[i][0] = C[i][i] = 1;
                for (int j = 1; j < i; j ++) {
                        C[i][j] = (C[i-1][j]+C[i-1][j-1])%MOD;
                }
        }
}

void add(int &a,int b) {
        a += b; 
        if (a>=MOD) a -= MOD;
}

void move(int dp[][N<<1],int sz,int cnt) {
        for (int i = n; i >= 0; i --) {
                for (int j = W; j >= 0; j --) if (dp[i][j]) {
                        int val = dp[i][j];
                        for (int k = 1; k <= cnt; k ++) {
                                if (i+k>n || j+k*sz>W) break;
                                add(dp[i+k][j+k*sz],(lld)val*C[i+k][k]%MOD);
                        }
                }
        }
}

int work() {
        vector<pair<int,int> > z;
        int sum = 0,ret = 0;
        for (int i = 1; i <= W; i ++) if(cnt[i]) {
                z.push_back(make_pair(i,cnt[i]));
                sum += i*cnt[i];
        }
        int sz = (int)z.size();

        int pcnt = 0;
        for (int i = 0; i < sz; i ++) {
                int val = i==0 ? 1 : pre[i-1];
                int cc = z[i].second;
                pre[i] = (lld)val*C[pcnt+cc][cc]%MOD;
                pcnt += cc;
        }
        if (sum<=W) ret = pre[sz-1];


        for (int i = 0; i <= n; i ++) {
                for (int j = 0; j <= W; j ++) {
                        dp[0][i][j] = 0;
                }
        }
        dp[0][0][0] = 1;
        int left = sum;
        pcnt = n;
        for (int k = sz-1; k >= 0; k --) {
                int cnt = z[k].second;
                int num = z[k].first;
                for (int i = 0; i <= n; i ++) {
                        for (int j = 0; j <= W; j ++) {
                                dp[1][i][j] = dp[0][i][j];
                        }
                }
                move(dp[1],num,cnt-1);
                left -= cnt*num;
                pcnt -= cnt;
                int val = k==0 ? 1 : pre[k-1];
                for (int i = max(0,W-left-num+1); i <= W-left; i ++) {
                        for (int j = 0; j <= n; j ++) {
                                add(ret,(lld)dp[1][j][i]*C[j+pcnt][pcnt]%MOD*val%MOD);
                        }
                }
                move(dp[0],num,cnt);
        }

        return ret;
}

int main() {
        init();
        int cas,ca = 0;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d%d",&n,&W);
                memset(cnt,0,sizeof(cnt));
                for (int i = 0; i < n; i ++) {
                        int x;
                        scanf("%d",&x);
                        cnt[x] ++;
                }
                printf("Case %d: %d\n",++ca,work());
        }
        return 0;
}

/*

33333
2 5
2 4

*/