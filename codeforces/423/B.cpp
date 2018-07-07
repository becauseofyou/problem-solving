#include <bits/stdc++.h>
using namespace std;

char mp[110][110];
int sum[110][110];

int Sum(int x, int y) {
	if(x < 0 || y < 0) {
		return 0;
	}
	return sum[x][y];
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int left = 100, right = -1, up = 100, down = -1;
	for (int i = 0; i < n; i++) {
		scanf("%s", mp[i]);
		for (int j = 0; j < m; j++) {
			if(mp[i][j] == 'B') {
				if (i < up) {
					up = i;
				}
				if (i > down) {
					down = i;
				}
				if (j < left) {
					left = j;
				}
				if (j > right) {
					right = j;
				}
			}
			sum[i][j] = Sum(i - 1, j) + Sum(i, j - 1) - Sum(i - 1, j - 1) + (mp[i][j] == 'B');
		}
	}
	if (left == 100) {
		puts("1");
	} else {
		int ret = -1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (j <= left && i <= up) {
					for (int edge = 1; edge <= 100; edge++) {
						if (i + edge - 1 < n && j + edge - 1 <  m && i + edge - 1 >= down && j + edge - 1 >= right) {
							int tmp = sum[i + edge - 1][j + edge - 1];
							if (ret == -1 || edge * edge - tmp < ret) {
								ret = edge * edge - tmp;
								// cout << edge << " " << i << " " << j << endl;
							}
						}
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}