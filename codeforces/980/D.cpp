#include <bits/stdc++.h>
using namespace std;

const int N = 5050;
int pre[N], a[N], ret[N];

int p[N], b[N];

int main () {
	int n;
	scanf("%d", &n);
	map<int,int> mp;
	int tot = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
		int tmp = 1;
		int neg = a[i] < 0;
		a[i] = abs(a[i]);
		for (int j = 2; j * j <= a[i]; j++) {
			int cnt = 0;
			while (a[i] % j == 0) {
				a[i] /= j;
				cnt++;
			}
			if (cnt & 1) {
				tmp *= j;
			}
		}
		if ( a[i] != 1) {
			tmp *= a[i];
		}
		if (neg) tmp *= -1;
		if (mp.find(tmp) == mp.end()) {
			mp[tmp] = tot++;
		}
		a[i] = mp[tmp];
		//cout << a[i] << " ";
	}	
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		memset(p, 0, sizeof(p));
		bool flag = true;
		bool has = false;
		for (int j = i; j < n; j++) {
			if (b[j] == 0) {
				has = true;
				if (j == i) {
					cnt++;
				} 
				ret[cnt]++;
				continue;
			}
			if (p[a[j]] == 0) {
				if(has && flag) {
				} else {
					cnt++;
				}
				p[a[j]] = 1;
			}
			ret[cnt]++;
			flag = false;
		}
		if (cnt == 0) {
			ret[1] ++;
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", ret[i]);
	}
	return 0;
}