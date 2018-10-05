#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	int cnt = 0;
	for (int i = 0; i < (int)s.length(); i++) {
		cnt += s[i] == '8';
	}
	cout << min(n / 11, cnt) << endl;
	return 0;
}