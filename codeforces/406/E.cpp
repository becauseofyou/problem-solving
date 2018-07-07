#include <bits/stdc++.h>
using namespace std;
const int N = 100010;

struct Tree *C;
struct Tree {
	Tree *lc, *rc;
	int cnt;
	bool left_end;
	Tree(int l = 0, int r = 0): cnt(0),left_end(false) {
		if(l == r) {
			return ;
		}
		int m = l + r >> 1;
		lc = new (C++) Tree(l, m);
		rc = new (C++) Tree(m + 1, r);
	}
	Tree *Insert(int position, int value, int l, int r)  {
		Tree *ta = new (C++)Tree();
		ta->lc = lc;
		ta->rc = rc;
		ta->left_end = left_end;
		ta->cnt = cnt;
		
		if (l == r) {
			ta->cnt += value;
			if(ta->cnt == 1) {
				ta->left_end = true;
			} else {
				ta->left_end = false;
			}
			return ta;
		}
		int m = l + r >> 1;
		if (position <= m) {
			ta->lc = lc->Insert(position, value, l, m);
		} else {
			ta->rc = rc->Insert(position, value, m + 1, r);
		}
		ta->left_end = ta->lc->left_end;
		ta->cnt = ta->lc->cnt + ta->rc->cnt;
		return ta;
	}
	int Query(int k, int l, int r) {
		if (cnt <= k) {
			return r;
		}
		if (l == r) {
			return l;
		}
		int m = l + r >> 1;
		if (lc->cnt > k) {
			return lc->Query(k, l, m);
		} else if (lc->cnt == k){
			if (!rc->left_end) {
				return rc->Query(k - lc->cnt, m + 1, r);
			} else {
				return lc->Query(k, l, m);
			}
		} else {
			return rc->Query(k - lc->cnt, m + 1, r);
		}
	}
}pool[N * 40], *root[N];
int mp[N], ret[N], a[N];

int main () {
	C = pool;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	root[n] = new (C++)Tree(0, n - 1);
	memset (mp, -1, sizeof(mp));
	for (int i = n - 1; i >= 0; i--) {
		if (mp[a[i]] != -1) {
			root[i] = root[i + 1]->Insert(mp[a[i]], -1, 0, n - 1);
			root[i] = root[i]->Insert(i, 1, 0, n - 1);
		} else {
			root[i] = root[i + 1]->Insert(i, 1, 0, n - 1);
		}
		mp[a[i]] = i;
	}
	for (int len = 1; len <= n; len++) {
		int pos = 0, ret = 0;
		while(pos < n) {
			int next_pos = root[pos]->Query(len, 0, n - 1);
			ret ++;
			pos = next_pos + 1;
		}
	    printf("%d ", ret);
	}
	return 0;
}
