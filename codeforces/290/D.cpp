#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 333;
const int INF = (int)1e9;
int len[N], cost[N];
vector<int> fac;
int dp[200010];
int ID(int x)
{
        return lower_bound(fac.begin(), fac.end(), x) - fac.begin();
}
void CheckMin(int &x, int y)
{
        if(x > y) x = y;
}
int main()
{
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
                scanf("%d", &len[i]);
                for(int j = 1; j * j <= len[i]; j++) {
                        if(len[i] % j == 0) {
                                fac.push_back(j);
                                fac.push_back(len[i] / j);
                        }
                }
        }
        for(int i = 0; i < n; i++) {
                scanf("%d", &cost[i]);
        }
        sort(fac.begin(), fac.end());
        fac.erase(unique(fac.begin(), fac.end()), fac.end());
        fill(dp, dp + (int) fac.size(), INF);
        for(int i = 0; i < n; i++) {
                CheckMin(dp[ID(len[i])], cost[i]);
                for(int j = 0; j < (int) fac.size(); j++) {
                        if(dp[j] != INF) {
                                CheckMin(dp[ID(__gcd(fac[j], len[i]))], dp[j] + cost[i]);
                        }
                }
        }
        if(dp[0] == INF) {
                dp[0] = -1;
        }
        printf("%d\n", dp[0]);
        return 0;
}
