#include <bits/stdc++.h>
using namespace std;

int main () {
	long long l, r, k;
	cin >> l >> r >> k;
	long long number = 1;
	bool flag = false;
	while (true) {
		if (number >= l && number <= r) {
			flag = true;
			cout << number << " " ;
		}
		if (number > r / k) {
			break;
		}
		number = number * k;
	}
	if (!flag)
	puts("-1");
	return 0;
}