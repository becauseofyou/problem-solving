#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
        int tot = 0, t;
        scanf("%d", &t);
        while(t--) {
                double a, b, c, d;
                scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
                if(((a<=56 && b <= 45 && c <= 25.0)  || a+b+c<=125 )&& d <= 7.0) {
                        printf("1\n");
                        tot++;
                }
                else    puts("0");
        }
        printf("%d\n", tot);
        return 0;
}