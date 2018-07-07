#include <bits/stdc++.h>
using namespace std;

int a[1010];
int n, k;
void print(int i, int a_i, int base, int a_base) {
	int should = a_base + (i - base) * k;
	if (a_i < should) {
		printf("+ %d %d\n", i + 1, should - a_i);
	} 
	if (a_i > should) {
		printf("- %d %d\n", i + 1, a_i - should);
	}
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	int ret = n, id = 0;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		bool flag = false;
		for (int j = 0; j < n; j++) if (i != j) {
			if (a[i] + k * (j - i) <= 0) {
				flag = true;
				break;
			}
			if (a[i] + k * (j - i) != a[j]) {
				cnt++;
			}
		}
		if (flag) {
			continue;
		}
		if (cnt < ret) {
			ret = cnt;
			id = i;
		}
	}
	printf ("%d\n", ret);
	for (int i = 0; i < n; i++) {
		print(i, a[i], id, a[id]);
	}
	return 0;
}
