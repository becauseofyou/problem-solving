/*
   有一个环，相邻两个数差值绝对值1
   让你用不超过60次询问找出是否有两个位置 a_i a_{i+n/2} 相同

   令d[i] 表示d[i]-d[i+n/2]的值
   那么d[i]与d[i+n/2]互为相反数

   然后我们知道对于d[i]与d[i+1]他们的差值为{-2,0,2}
   因此可以判断所有的d的值得奇偶性相同
   
   因此如果有一个d值为奇数，意味着所有的d都是奇数，不可能为0
   就不可能存在相同的a_i a_{i+n/2}

   如果d值为偶数，由于从d[i]到d[i+n/2]每次+2 或者 -2 或者不变
   那么这个过程会经过d[i]与d[i+n/2]之间的所有的偶数
   由于他们符号不同，所以肯定会存在一个时刻d[j] = 0

   我们令l = 1, r = 1 + n / 2;
   m = (l + r) / 2
   我们检查d[m]的值，
   如果d[m]=0就可以结束了
   如果d[m] 与 d[l]的符号一样，说明零点在
   m + 1 -> r之间
   否则在l->m-1之间
    也就是说我们可以二分
   */
#include <bits/stdc++.h>
using namespace std;

int n;
int ask(int pos) {
    printf("? %d\n", pos);
    fflush(stdout);
    int number1, number2;
    scanf("%d", &number1);

    printf("? %d\n", pos + n);
    fflush(stdout);
    scanf("%d", &number2);
    return number1 - number2;
}


int main() {
    scanf("%d", &n);
    n /= 2;
    if (n % 2) {
        puts("! -1");
        return 0;
    }

    int l = 1, r = n;
    int x = ask(1);
    if (x == 0) {
        printf("! 1\n");
        return 0;
    }
    int sign = x < 0 ? -1 : 1;
    while (l <= r) {
        int m = (l + r) / 2;
        int x = ask(m);
        if (x == 0) {
            printf("! %d\n", m);
            return 0;
        }
        int sx = x < 0 ? -1 : 1;
        if (sx == sign) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return 0;
}
