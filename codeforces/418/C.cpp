#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int> > a[26];

int num[1500][1501];
int mx[1555];
char s[1555];
inline void Update(int &x, int y) {
  if(y > x) {
    x = y;
  }
}

int main () {
  int n;
  scanf("%d", &n);
  scanf("%s", s);
  for(int i = 0; i < n; i++) {
    int j = i;
    while(s[j] == s[i] && j < n) {
      j++;
    }
    a[s[i] - 'a'].push_back({j - i, j - 1}); // len, right_end
    i = j - 1;
  }
  memset(num, -1, sizeof(num));
  for(int i = 0 ;i < n; i++) {
    int cnt = 0;
    for(int j = i; j < n; j++) {
      if(s[j] != s[i]) {
        cnt++;
      }
      num[i][cnt] = j;
    }
    mx[i] = cnt;
  }
  int q;
  scanf("%d", &q);
  int ret = 0;
  int m; char tmp[2];
  for(int i = 0; i < q; i++) {
    scanf("%d%s", &m, tmp);
    int c = tmp[0]-'a';
    ret = m;
    int sz = (int)a[c].size();
    for(int j = 0; j < sz; j++) {
      int len = a[c][j].first;
      int end = a[c][j].second;
      int start = end - len + 1;
 //     printf("start=%d\n", start);
      if(m < mx[start]) {
        Update(ret, num[start][m] - start + 1);
      } else {
        Update(ret, n - 1 - start + 1 + m - mx[start]);
      }
    }
    if(ret > n) ret = n;
    printf("%d\n", ret);
  }
  return 0;
}