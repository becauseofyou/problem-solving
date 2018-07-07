#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 30000010;
long long sum[N];
void init() {
	for(int g = 1; g < N; g++) {
		for(int i = g; i + g < N; i += g) if((i ^ (i + g)) == g){
			int a = i, b = i + g;
			while(a > 0 && b > 0) {
				int tmp = a % b;
				a = b; b = tmp;
			}
			int gcd = a + b;
			if(gcd == g) {
				sum[i + g]++;
			}
		}
	}
	for(int i = 2; i < N; i++) {
		sum[i] += sum[i - 1];
	}
}
int main() {
	init();
	int t, ca = 1, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		/*
		int c = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = i; j <= n; j++) {
				if(__gcd(i , j) == (i ^ j)) c++;
			}
		}
		printf("%d\n",c);
		*/
		printf("Case %d: %lld\n", ca ++, sum[n]);
	}
	return 0;
}