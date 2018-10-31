#include <bits/stdc++.h>
using namespace std;

const int md = 998244353;
const int N = 1000010;

inline int add(int &a, int b) {
	a += b;
	if (a >= md) a -= md;
    return a;
}

inline int sub(int a, int b) {
	a -= b;
	if (a < 0) a += md;
    return a;
}

inline int mul(int a, int b) {
	return (long long) a * b % md;
}

inline int power(int a, int b) {
	int res = 1;
	while (b > 0) {
		if (b & 1) {
			res = mul(res, a);
		}
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

int inv[N], fac[N];
int C(int n, int m) {
    return mul(mul(fac[n] , inv[m]) , inv[n - m]);
}

int main() {
	int n;
	cin >> n;
    fac[0] = 1; 
    for (int i = 1; i <= n; i++) {
        fac[i] = mul(fac[i - 1],  i);
    }
    inv[n] = power(fac[n], md - 2);
    for (int i = n - 1; i >= 0; i--) {
        inv[i] = mul(inv[i + 1] , i + 1);
    }
    //至少有一行同色行的方案数
	int result = sub(power(power(3, n), n), power(sub(power(3,n), 3), n) );
    //加上至少有一列同色列的方案数
    //同时有同色行和同色列的情况会被多算
    //因此在加上至少有一列同色列的方案的时候应该避免加上这些重复的方案
    //考虑容斥，枚举至少有几列同色列
    for (int i = 1; i <= n; i++) {
        // 枚举的同色列们只有一种颜色,此时不能有同色行, power(3, n - i) - 1:每一行的方案数
        int _same = mul(mul(3, C(n, i)), power(sub(power(3, n - i), 1), n));
        // 枚举的同色列有多种颜色 剩下的列随意
        int _multi = mul(mul(C(n, i), sub(power(3, i), 3)), power(power(3, n), n - i));
        int total = 0;
        total = add(total, _same); 
        total = add(total, _multi);
        if (i & 1) {
            result = add(result, total);
        } else {
            result = sub(result, total);
        }
    }
    cout << result << endl;

	return 0;
}
