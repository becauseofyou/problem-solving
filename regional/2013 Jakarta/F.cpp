#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef unsigned long long llu;
const int N = 50500;
const llu X = 1643;
char s[N];
int len;
llu px[N],pa[N];

llu get(int l,int r) {
        return pa[l]-pa[r+1]*px[r-l+1];
}

int work() {
        len = strlen(s);
        pa[len] = 0;
        for (int i = len-1; i >= 0; i --) {
                pa[i] = pa[i+1]*X+s[i]-'A'+1;
        }
        int l = 0,r = len-1,lp = -1,rp = len;
        int ret = 0;
        while (true) {
                lp ++;
                rp --;
                if (lp>=rp) {
                        break;
                }
                if (get(l,lp)==get(rp,r)) {
                        l = lp+1;
                        r = rp-1;
                        ret += 2;
                }
        }
        ret += l<=r;
        return ret;
}

int main() {
        int cas,ca = 0;
        scanf("%d",&cas);
        px[0] = 1;
        for (int i = 1; i < N; i ++) px[i] = px[i-1]*X;
        while (cas--) {
                scanf("%s",s);
                printf("Case #%d: %d\n",++ca,work());
        }
        return 0;
}