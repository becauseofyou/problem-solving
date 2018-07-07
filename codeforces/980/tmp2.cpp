#include<bits/stdc++.h>

using std :: vector;
using std :: reverse;

#define For(i, _l, _r) for (int i = (_l), i##r = (_r); i <= (i##r); ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r); i >= (i##r); --i)
#define Rep(i, _l, _r) for (int i = (_l); i; i = (_r))
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> T max(T x, T y) { return (x > y)? x: y; }
template <typename T> T min(T x, T y) { return (x < y)? x: y; }
template <typename T> bool chkmax(T &x, T y) { return (x >= y)? 0: (x = y, 1); }
template <typename T> bool chkmin(T &x, T y) { return (x <= y)? 0: (x = y, 1); }

template <typename T>
T read(T &in) {
	in = 0; char ch; T f = 1;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	while (isdigit(ch)) in = in * 10 + ch - '0', ch = getchar();
	return in *= f;
}

static const int max1 = 500000 + 11;
static const int max2 = 2000000 + 11;

int Ct = 1, Ht[max1], Nt[max2], to[max2];

void ins(int x, int y) {
	Nt[++Ct] = Ht[x], Ht[x] = Ct, to[Ct] = y;
	Nt[++Ct] = Ht[y], Ht[y] = Ct, to[Ct] = x;
}

int n, m;
int dt, dfn[max1], low[max1]; bool isB[max2], vis[max1];
int stack[max1], *top = stack;
int cnt, atC[max1];

int mL[max1], L[max1], Z[max1];

vector<int> C[max1];

void Tarjan(int x, int fa) {
	int y;
	dfn[x] = low[x] = ++dt, *(++top) = x;
	Rep(i, Ht[x], Nt[i]) if (to[i] != fa) {
		y = to[i];
		if (!dfn[y]) {
			Tarjan(y, x), chkmin(low[x], low[y]);
			if (low[y] > low[x]) isB[i] = isB[i ^ 1] = 1;
		} else chkmin(low[x], dfn[y]);
	}
	if (dfn[x] != low[x]) return;
	++cnt;
	do {
		y = *(top--);
		atC[y] = cnt;
		C[cnt].push_back(y);
	} while (x != y);
}

void GetBfsTree() {
	static int que[max1], fa[max1];
	int *front = que, *back = que;
	
	*(++back) = 1, vis[1] = 1;
	while (front < back) {
		int x = *(++front);
		Rep(i, Ht[x], Nt[i]) if (!vis[to[i]])
			vis[to[i]] = 1, fa[to[i]] = x, *(++back) = to[i];
	}
	
	Lop(_q, n, 1) {
		int x = que[_q];
		Rep(i, Ht[x], Nt[i]) if (fa[to[i]] == x) {
			chkmax(mL[x], mL[to[i]] + 1);
			if (isB[i]) chkmax(L[x], mL[to[i]] + 1);
		}
	}
}

void solve(int now, int fa, int upd) {
	static int q[max2], que[max2];
	int *front = que + 1, *back = que;
	
	chkmax(L[now], upd);
	
	int qt = (int)C[atC[now]].size();
	For(i, 1, qt) q[i] = q[i + qt] = C[atC[now]][i - 1];
	
	For(twice, 0, 1) {
		front = que + 1, back = que;
		Lop(i, (qt >> 1) + qt, 1 + qt) {
			while (front <= back && L[q[i]] + i > L[q[*back]] + *back) --back;
			*(++back) = i;
		}
		
		Lop(i, qt, 1) {
			while (front <= back && *front - i > (qt >> 1)) ++front;
			if (front <= back) chkmax(Z[q[i]], L[q[*front]] + *front - i);
			while (front <= back && L[q[i]] + i > L[q[*back]] + *back) --back;
			*(++back) = i;
		}
		
		reverse(1 + q, 1 + (qt << 1) + q);
	}
	
	vector<int> :: iterator x;
	for (x = C[atC[now]].begin(); x != C[atC[now]].end(); ++x) {
		int fMax = 0, sMax = 0;
		Rep(i, Ht[*x], Nt[i]) if (to[i] != fa && isB[i]) {
			if (chkmax(sMax, mL[to[i]] + 1)) {
				if (sMax > fMax) std :: swap(sMax, fMax);
			}
		}
		Rep(i, Ht[*x], Nt[i]) if (to[i] != fa && isB[i]) {
			int n_upd = max(Z[*x], upd);
			if (mL[to[i]] + 1 == fMax) chkmax(n_upd, sMax);
			else chkmax(n_upd, fMax);
			
			solve(to[i], *x, n_upd + 1);
		}
	}
}

int main() {
	
	read(n), read(m);
	For(i, 1, m) {
		int x, y;
		read(x), read(y);
		ins(x, y);
	}
	
	Tarjan(1, 0);
	
	GetBfsTree();
	
	solve(1, 0, 0);
	
	For(i, 1, n) printf("%d ", max(L[i], Z[i])); putchar(10);
	
	return 0;
}