#include <bits/stdc++.h>
using namespace std;

int mp[256];
string name[] = {"Kuro", "Shiro", "Katie"};
int main() {
	int n;
	cin >> n;
	string s[3];
	int ret = 0;
	bool flag = true;
	int id = -1;
	int len = 0;
	std::vector<pair<int,int> > num;
	for (int i = 0; i < 3; i++) {
		cin >> s[i];
		len = (int)s[i].length();
		memset(mp, 0, sizeof(mp));
		for (int j = 0; j < len; j++) {
			mp[s[i][j]] ++;
		}
		int mx = *max_element(mp, mp + 256);
		if (mx + n > len) {
			if (mx == len) {
				if ( n == 1) {
					mx--;
				}
			} else {
				mx = len;
			}
		} else {
			mx += n;
		}
		num.push_back(make_pair(mx, i));
	}
	sort(num.begin(), num.end());
	//cout << num[2].first << " " << num[1].first << endl;
	if(num[2].first == num[1].first) {
		cout << "Draw" << endl;
	} else {
		cout << name[num[2].second] << endl;
	}
	return 0;
}