#include <bits/stdc++.h>
using namespace std;

// a ^ 11 = a ^ 1 * a ^ 2 * a ^ 8
// 1011
/*
   a^1  ret = ret * a ;
   a^2  ret = ret * a ;
   a^4
   a^8  ret = ret * a ;
   a^16
   a^32

   O(log n)
   */
int pow_mod(int a, int b, int c) {
    int ret = 1 % c;
    while (b > 0) {
        if (b & 1) {
            ret = 1LL * ret * a;
        }
        a = 1LL * a * a % c;
        b >>= 1;
    }
    return ret;
}
int main() { 
    return 0;
}
