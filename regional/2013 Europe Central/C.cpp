#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

#define mp make_pair
#define pb push_back
#define snuke(it,x) for ((__typeof((x).begin())) it = (x).begin(); it != (x).end(); it ++)
typedef long long lld;
typedef pair<int,int> PII;

const int N = 101000;
lld a[N];
int n,next[N];

lld work() {
        lld ret = 0;
        for (int i = 1; i <= n; i ++) {
                ret = max(ret,a[i]);
                int p = i;
                for (int j = next[i]; j > 0; j = next[j]) {
                        a[j] = __gcd(a[j],a[i]);
                        ret = max(ret,a[j]*(i-j+1));
                        if (a[j]==a[p]) {
                                next[p] = j;
                        } else {
                                p = j;
                        }
                }
        }
        return ret;
}

int main() {
        int cas;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d",&n);
                for (int i = 1; i <= n; i ++) {
                        scanf("%lld",a+i);
                        next[i] = i-1;
                }
                printf("%lld\n",work());
        }
        return 0;
}

