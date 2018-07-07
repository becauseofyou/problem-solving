#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;


const int N = 1010;
char s[N];
int cnt[26];

int main() {
	int cas,ca = 0;
	scanf("%d",&cas);
	while (cas--) {
		scanf("%s",s);
		int len = strlen(s),ans = 0;
		for (int i = 0; i < len; i ++) {
			memset(cnt,0,sizeof(cnt));
			int num = 0;
			for (int j = i; j < len; j ++) {
				int c = s[j]-'a';
				cnt[c] ++;
				if (cnt[c]%2==0) {
					num  --;
				} else {
					num ++;
				}
				if (num<=1) {
					ans ++;
				}
			}
		}
		printf("Case %d: %d\n",++ca,ans);
	}
	return 0;
}