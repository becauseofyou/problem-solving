#include <cstdio>
typedef long long lld;
lld c[2][2][1010][1010];
void update(int x,int y,int v) {
    int xx = x&1, yy = y&1;
    for(int a = x; a <= 1000; a += a&-a) {
        for(int b = y; b <= 1000; b += b&-b) {
            c[xx][yy][a][b] ^= v;
        }
    }
}
lld query(int x,int y) {
    lld ans=0;
    int xx = x&1, yy = y&1;
    for(int a = x; a > 0; a -= a&-a) {
        for(int b = y; b > 0; b -= b&-b) {
            ans ^= c[xx][yy][a][b];
        }
    }
    return ans;
}
void update(int x1,int y1,int x2,int y2,lld v) {
    update(x1,y1,v);
    update(x2,y2,v);
    update(x1,y2,v);
    update(x2,y1,v);
}
int main() {
    int n, m, op, x0, y0, x1, y1;
    lld v;
    scanf("%d%d",&n,&m);
    while(m--) {
        scanf("%d%d%d%d%d",&op,&x0,&y0,&x1,&y1);
        if(op == 1) {
            x0 -- ;
            y0 -- ;
        } else {
            x1 ++ ;
            y1 ++ ;
        }
        if(op == 1) {
            printf("%I64d\n",query(x1,y1)^query(x0,y0)^query(x0,y1)^query(x1,y0));
        } else {
            scanf("%I64d",&v);
            update(x0,y0,x1,y1,v);
        }
    }
    return 0;
}
