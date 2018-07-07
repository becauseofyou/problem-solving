#include <cstdio>
#include <algorithm>
using namespace std;
typedef long  long lld;
lld a[100010];
lld gcd(lld a,lld b) {
    return !b ? a: gcd(b,a%b);
}
int main() {
    int n;
    scanf("%d",&n); 
    lld s = 0;
    for(int i = 1; i <= n; i++){
         scanf("%I64d",&a[i]);
         s += a[i];
    }
    sort(a+1,a+1+n);
    lld sum = 0;
    lld p = n-1, pre = 0;
    for(int i = n; i >= 1; i--) {
        sum += p * a[i]; 
        sum -= pre * a[i];
        p --;
        pre ++;
    }
   //printf("sum=%I64d\n",sum);
    sum*=2;
    sum += s;
    lld g = gcd(sum,n);
    printf("%I64d %d\n",sum/g,n/g);
    return 0;
}
