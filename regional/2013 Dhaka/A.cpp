#include <cstdio>

int main() {
	int n;
	while(scanf("%d", &n) == 1 && n) {
		int mx = 0, ans = 0;
		for(int i = 0;i < n ;i++) {
			int l, w, h;
			scanf("%d%d%d", &l, &w, &h);
			if(h > mx || (h == mx && ans < l*w*h)) {
				mx = h;
				ans = l*w*h;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

