#include <bits/stdc++.h>
using namespace std;

char s[100010];
int main () {
	int n;
	scanf("%d", &n);
	string ret = "";
	int number_zero = 0;
	bool flag = false;
	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		if(strcmp (s, "0") == 0) {
			flag = true;
		}
		int cnt = 0;
		bool other = false;
		for (int j = 0; s[j]; j++) {
			if (s[j] == '1') {
				cnt++;
			}
			if (s[j] != '1' && s[j] != '0') {
				other = true;
			}
		}
		if (cnt > 1 || other)  {
			ret = s;
		} else {
			number_zero += strlen(s) - 1;
		}
	}
	if (flag) {
		puts("0");
	} else {
		if(ret != "") {
			cout << ret;
		} else {
			cout << "1";
		}
		for(int i = 0; i < number_zero; i++) printf("0");
	}
	return 0;
}