#include <bits/stdc++.h>
using namespace std;

int main () {
	int n, a, b, t;
	scanf ("%d%d%d", &n, &a, &b);
	int left_a = a, left_b = b, left_b1 = 0;
	int ret = 0;
	for (int i = 0 ; i < n; i++) {
		scanf("%d", &t);
		if (t == 1) {
			if (left_a) {
	            left_a --;
			} else {
				if (left_b) {
					left_b--;
					left_b1++;
				} else if(left_b1) {
					left_b1--;
				} else {
					ret++;
				}
			}
		} else {
			if (left_b) {
				left_b--;
			} else {
				ret += 2;
			}
		}
	}
	printf("%d\n",ret);
	return 0;
}