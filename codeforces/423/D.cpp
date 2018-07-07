#include <bits/stdc++.h>


const int N = 200010;

int end[N];

int main () {
	int n, k;
	scanf("%d%d", &n, &k);
	int len = (n - 1) / k;
	int left = (n - 1) % k;
	int ret = left == 0 ? len + len : (left == 1 ? len + len + 1 : len + len + 2);
	std::fill (end, end + n, 1);
	int nodeid = 2;
	printf("%d\n", ret);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < len; j++) {
			printf("%d %d\n", end[i], nodeid);
			end[i] = nodeid;
			nodeid++;
		}
	}
	for (int i = 0; i < left; i++) {
		printf("%d %d\n", end[i], nodeid);
		nodeid++;
	}
	return 0;
}
