#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long lld;
const int N = 1001000;
const int MOD = (int)1e9+7;

struct Sgt {
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
        int xsum[N<<2][4],t[N<<2],delta[N<<2][4];
        void build(int l,int r,int rt) {
                for (int i = 0; i < 4; i ++) {
                        delta[rt][i] = 0;
                }
                t[rt] = 0;
                if (l==r) {
                        int val = 1;
                        for (int i = 0; i < 4; i ++) {
                                xsum[rt][i] = val;
                                val = (lld)val*l%MOD;
                        }
                        return ;
                }
                int mid = l+r>>1;
                build(lson);
                build(rson);
                for (int i = 0; i < 4; i ++) {
                        xsum[rt][i] = (xsum[rt<<1][i]+xsum[rt<<1|1][i])%MOD;
                }
        }
        void update(int rt,int *dt) {
                for (int i = 0; i < 4; i ++) {
                        t[rt] = (t[rt]+(lld)dt[i]*xsum[rt][i]%MOD)%MOD;
                        delta[rt][i] = (delta[rt][i]+dt[i])%MOD;
                }
        }
        void down(int rt) {
                update(rt<<1,delta[rt]);
                update(rt<<1|1,delta[rt]);
                for (int i = 0; i < 4; i ++) {
                        delta[rt][i] = 0;
                }
        }
        void up(int rt) {
                t[rt] = (t[rt<<1]+t[rt<<1|1])%MOD;
        }
        void modify(int L,int R,int *dt,int l,int r,int rt) {
                if (L<=l && r<=R) {
                        update(rt,dt);
                        return ;
                }
                int mid = l+r>>1;
                down(rt);
                if (L<=mid) modify(L,R,dt,lson);
                if (R>mid)  modify(L,R,dt,rson);
                up(rt);
        }
        int query(int L,int R,int l,int r,int rt) {
                if (L<=l && r<=R) {
                        return t[rt];
                }
                int mid = l+r>>1,ret = 0;
                down(rt);
                if (L<=mid) ret = (ret+query(L,R,lson))%MOD;
                if (R>mid)  ret = (ret+query(L,R,rson))%MOD;
                return ret;
        }
}sgt;

int main() {
        int cas,ca = 0,n;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d",&n);
                int l = 0,r = 1000000;
                sgt.build(l,r,1);
                printf("Case #%d:\n",++ca);
                while (n--) {
                        char s[13];
                        int a[4],x1,x2;
                        scanf("%s%d%d%d%d%d%d",s,&x1,&x2,a+0,a+1,a+2,a+3);
                        for (int i = 0; i < 4; i ++) {
                                a[i] = (a[i]%MOD+MOD)%MOD;
                        }
                        swap(a[0],a[3]);
                        swap(a[1],a[2]);
                        if (s[0]=='p') {
                                sgt.modify(x1,x2,a,l,r,1);
                        } else {
                                int val = sgt.query(x1,x2,l,r,1);
                                printf("%d\n",val);
                                int r1,r2;
                                r1 = (lld)x1*val%r;
                                r2 = (lld)x2*val%r;
                                if (r1>r2) swap(r1,r2);
                                sgt.modify(r1,r2,a,l,r,1);
                        }
                }
        }
        return 0;
}