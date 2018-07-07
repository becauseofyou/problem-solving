#include <cstdio>
const int mod = 1000000007;
const int N = 2010;
int a[N];
bool f[N];
long long dp[N];
int main() {
    int n;
    long long x=0,y=0;
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        if(a[i] != -1) f[a[i]] = true;
    }
    for(int i = 1; i <= n; i++)if(a[i]==-1) f[i] ? y++ : x++; 
    dp[0] = 1;
    for(int i = 1; i <= y; i++) dp[0] = dp[0] * i % mod;
    dp[1] = y * dp[0];
    for(int i = 2; i <= x; i++) dp[i] = (y * dp[i-1] + (i-1) * (dp[i-2] + dp[i-1]))%mod;
    printf("%I64d\n",dp[x]);
    return 0;
}
