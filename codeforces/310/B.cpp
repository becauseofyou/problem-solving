#include <bits/stdc++.h>
using namespace std;

int main () {
	int n;
	scanf("%d", &n);
	vector<int> a; 
	a.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	int delta = a[]0;
	bool flag = true;
	for (int i = 1; i < n; i++) {
		if (i & 1) {
			a[i] = (a[i] + delta) % n;
		} else {
			a[i] = (a[i] - delta + n) % n;
		}
		if (a[i] != i) {
			flag = false;
		}
	}
	puts(flag ? "Yes" : "No");
	return 0;
}
