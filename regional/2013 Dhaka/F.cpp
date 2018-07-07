#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}

int main() {
    int t, x1, y1, x2, y2, cas = 1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int x = abs(x1-x2), y = abs(y1-y2);
        int S = max(max(x1, y1), max(x2, y2));
        printf("Case %d: ", cas++);
        if(y1 == y2) {
            printf("0 0 %d %d\n", 0, 1);
        }
        else if(x1 == x2) {
            printf("0 0 %d %d\n", 1, 0);
        }
        else {
            if(x1 > x2) swap(x1, x2), swap(y1, y2);
            if(y1 < y2) printf("%d %d %d %d\n", S, 0, S-y, x);
            else    printf("0 0 %d %d\n", y, x);
        }
    }
    return 0;
}

