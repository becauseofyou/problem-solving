/* + - * / ( ) 0~9
(1 + 2) * 3 = 6

1 + 2 * 3 = 7

((1 + 2) * 3 + 5) * 6

1 / 2 = 0.5

表达式树

每次找到最后被计算的操作符，将问题划分成两个子问题
(1)+(1)
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
char s[N];


double calc(double a, double b, char ch) {
    if (ch == '+') return a + b;
    if (ch == '-') return a - b;
    if (ch == '*') return a * b;
    if (ch == '/') return a / b;
    if (ch == '^') return pow(a, b);
}

int mp[256];

void init() {
    memset(mp, -1, sizeof(mp));
    mp['^'] = 1;
    mp['*'] = mp['/'] = 2;
    mp['+'] = mp['-'] = 3;
}

bool prior(char a, char b) {
    return mp[a] >= mp[b];
}

double build(int l, int r) {
    if (l > r) {//-1-2
        return 0;
    }
   //寻找最后被计算的操作符的位置
    int p = -1;
    int v = 0;
    for (int i = l; i <= r; i++) {
        if (s[i] == '(') v++;
        if (s[i] == ')') v--;
        if (v == 0 && mp[s[i]] != -1) {
            if (p == -1) {
                p = i;
            } else {
                if (prior(s[i], s[p])) {
                    p = i;
                }
            }
        }
    }
    if (p == -1) {
        if (s[l] == '(' && s[r] == ')')  {
            return build(l + 1, r - 1);
        }
        double num = 0;
        int dot_pos = r + 1;
        for (int i = l; i <= r; i++) {
            if (s[i] == '.') {
                dot_pos = i;
                break;
            }
            num = num * 10 + s[i] - '0';
        } 
        double base = 0.1;
        for (int i = dot_pos + 1; i <= r; i++) {
            num = num + base * (s[i] -'0');
            base *= 0.1;
        }
        
        return num;
    }
    //递归解决左右两边的子问题
    double lvalue = build(l, p - 1);
    double rvalue = build(p + 1, r);
    return calc(lvalue, rvalue, s[p]);
}

int main() {
    init();
    scanf("%s", s);
    int len = strlen(s);
    printf("%.3f\n", build(0, len - 1) );
    return 0;
}
