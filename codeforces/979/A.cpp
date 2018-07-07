#include <bits/stdc++.h>
using namespace std;

int main() {
	long long n;
	cin >> n;
	n ++;
	if (n == 1) {
		printf("0");
		return 0;
	}
	if (n % 2 == 0) {
		cout << n / 2;
	} else {
		cout << n ;
	}
	return 0;
}
