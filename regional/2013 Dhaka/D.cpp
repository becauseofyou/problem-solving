#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 10100;

typedef long long lld;
const lld MOD = (lld)1e13+7;
lld table[110][N],F[N],Finv[N];

lld exgcd(lld a, lld b, lld &x, lld &y) {
	if(!b) {
		x = 1; y = 0;
		return a;
	}
	lld ret = exgcd(b, a%b, y, x);
	y -= a/b*x;
	return ret;
}

lld inv(lld a) {
	lld x, y, d = exgcd(a, MOD, x, y);
	if(x < 0) x += MOD;
	return x;
}

lld mul(lld a,lld b) {
	lld ret = 0;
	while (b) {
		if (b&1) ret = (ret+a)%MOD;
		a = (a+a)%MOD;
		b >>= 1;
	}
	return ret;
}

lld A(int a,int b) {
	return mul(F[a],Finv[a-b])%MOD;
}

void init() {
	F[0] = 1;
	for (int i = 1;  i < N; i ++) {
		F[i] = F[i-1]*i%MOD;
	}
	Finv[0] = 1;
	for (int i = 1; i < N; i ++) {
		Finv[i] = inv(F[i]);
	}
	for (int i = 1; i <= 100; i ++) {
		lld x = i*i;
		for (int j = 1; j <= i*i; j ++) {
			table[i][j] = (table[i][j-1]+x)%MOD;
			x = (x*(i*i-j))%MOD;
		}
	}
}

int main() {
	int cas,ca = 0;
	init();
	scanf("%d",&cas);
	while (cas--) {
		int l,n,m;
		scanf("%d%d%d",&l,&m,&n);
		printf("Case %d: %lld\n",++ca,(table[l][n]-table[l][m-1]+MOD)%MOD);
	}
	return 0;
}

