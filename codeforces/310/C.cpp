#include <bits/stdc++.h>
using namespace std;

int num[100010];
int main () {
	int n, k;
	scanf("%d%d", &n, &k);
	int divide = 0, cnt, chains = k;
	for (int i = 0; i < k; i++) {
		scanf("%d", &cnt);
		for (int j = 0; j < cnt; j++) {
			scanf("%d", &num[j]);
		}
		if (num[0] == 1) {
			for (int j = 1; j < cnt; j++) {
				if (num[j] != num[j - 1] + 1) {
					divide += cnt - j;
					chains += cnt - j;
					break;
				}
			}
		} else {
			divide += cnt - 1;
			chains += cnt - 1;
		}
	}
	//printf("divide=%d\n", divide);
	divide += chains - 1;
	printf("%d\n", divide);
	return 0;
}