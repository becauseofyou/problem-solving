#include <bits/stdc++.h>
using namespace std;

int main () {
	int k, a, b, v;
	scanf("%d%d%d%d", &k, &a, &b, &v);
	int boxes = b / (k - 1);
	int left = b % (k - 1);
	int pre = boxes * k * v;
	int last = (left + 1) * v;
	if (a <= pre) {
		printf("%d\n", (a + k * v - 1 ) / (k * v));
	} else {
		if (a > pre + last) {
			printf("%d\n", boxes + 1 + (a - pre - last + v - 1) / v);
		} else { 
			printf("%d\n", boxes + 1);
		}
	}
	return 0;
}
