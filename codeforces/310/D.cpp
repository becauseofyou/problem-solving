#include <bits/stdc++.h>
using namespace std;

const int N = 222222;

struct node {
	long long l, r;
	int id;
	void print () {
		printf("l=%lld r=%lld id=%d\n", l, r, id);
	}
	bool operator < (const node & cmp) const  {
		return r < cmp.r || r == cmp.r && l < cmp.l;
	}
};
vector <node> in;
int ans[N];
multiset <pair<long long, int> >st;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	long long l, r, pl, pr;
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", &l, &r);
		if (i) {
			in.emplace_back(node{l - pr, r - pl, i - 1});
		}
		pl = l, pr = r;
	}
	long long len;
	
	for (int i = 0; i < m; i++) {
		scanf("%lld", &len);
		st.insert({len, i});
	}
	sort (in.begin(), in.end());
	for (auto it : in) {
	//	it.print();
	}
	bool flag = true;
	for (auto it: in) {
		auto it2 = st.lower_bound({it.l, -1});
		if (it2 == st.end() || it2->first > it.r) {
			flag = false;
			break;
		} else {
			ans[it.id] = it2->second;
			st.erase(it2);
		}
	}
	if (false == flag) {
		printf("No\n");
		return 0;
	}
	printf("Yes\n");
	for (int i = 0; i < n - 1; i++) {
		printf("%d ", ans[i] + 1);
	}
	return 0;
}