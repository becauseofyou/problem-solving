#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

long long make_perfect[N], sum[N];
int a[N], id[N], answer[N];

long long cost_change_to(int minimum_index) {
	return 1LL * minimum_index * a[id[minimum_index]] - sum[minimum_index];
}

bool checkmax(long long &ret, long long cmp) {
	if (cmp > ret) {
		ret = cmp;
		return true;
	}
	return false;
}

int main() {
	int n, A, coeffient_max, coeffient_min;
	long long total;
	cin >> n >> A >> coeffient_max >> coeffient_min >> total;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		id[i] = i;
	}
	sort (id, id + n, [](int i, int j) {return a[i] < a[j];});
	for (int i = 0; i < n; i++) {
		sum[i + 1] = sum[i] + a[id[i]];
	}
	long long cost = 0;
	for (int i = n - 1; i >= 0; i--) {
		cost += A - a[id[i]];
		make_perfect[n - i] = cost;
	}

	int minimum_index = n - 1, perfect_number = -1;
	long long ret = 0, minimum = -1;
	if (cost <= total) {
		ret = 1LL * n * coeffient_max + 1LL * A * coeffient_min;
		perfect_number = n;
		minimum = A;
	} else {
		for (int perfect = 0; perfect <= n; perfect++) {
			long long remain_unit = total - make_perfect[perfect];
			if (remain_unit < 0) {
				break;
			}

			while (minimum_index >= 0 && cost_change_to(minimum_index) > remain_unit) {
				minimum_index --;
			}
			while (minimum_index >= n - perfect) {
				minimum_index--;
			}
	#ifndef ONLINE_JUDGE
		//printf("minimum_index=%d\n", minimum_index);
	#endif
			long long remain_unit_to_make_larger = remain_unit - cost_change_to(minimum_index);

			long long add = remain_unit_to_make_larger / (minimum_index + 1);
			long long minimum_value = a[id[minimum_index]] + add;
			minimum_value = min(minimum_value, 1LL * A);
			if(checkmax(ret, 1LL * minimum_value * coeffient_min + 1LL * coeffient_max * perfect)) {
				perfect_number = perfect;
				minimum = minimum_value;
			}
		}
	}
	for (int i = n - perfect_number; i < n; i++) {
		answer[id[i]] = A;
	}
	for (int i = 0; i < n - perfect_number; i++) {
		answer[id[i]] = a[id[i]] < minimum ? minimum : a[id[i]];
	}
	cout << ret << endl;
	for (int i = 0; i < n; i++) {
		printf("%d ", answer[i]);
	}
	return 0;
}