#include <bits/stdc++.h>
using namespace std;

int calc(long long num) {
	int ret = 0;
	while (num) {
		ret += num % 10;
		num /= 10;
	}
	return ret;
}
int main() {
	long long n;
	cin >> n;
	long long num = 0;
	while (num * 10 + 9 <= n) {
		num = num * 10 + 9;
	}
	cout << calc(num) + calc(n - num) << endl;
	return 0;
}