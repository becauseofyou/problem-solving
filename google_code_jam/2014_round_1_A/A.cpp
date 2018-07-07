#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 210;
string s[N], ss[N];
string tmp[N], tmp2[N];
int main() {
  int t, ca = 1;
  freopen("A-large.in","r",stdin);
  freopen("A-large.out","w",stdout);
  cin >> t;
  while(t--) {
    int n, L;
    cin >> n >> L;
    for(int i = 0; i < n; i++) {
      cin >> s[i];
    }
    for(int i = 0; i < n; i++) {
      cin >> ss[i];
    }
    bool flip[110];
    int ret = -1;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        tmp[j] = s[j];
        tmp2[j] = ss[j];
      }
      int cnt = 0;
      for(int j = 0; j < L; j++) {
        if(s[0][j] != ss[i][j]) {
          cnt++;
          for(int k = 0; k < n; k++) {
            tmp[k][j] = '1' - tmp[k][j] + '0';
          }
        }
      }
      sort(tmp, tmp + n);
      sort(tmp2, tmp2 + n);
      bool flag = true;
      for(int j = 0; j < n; j++) {
        if(tmp[j] != tmp2[j]) {
          flag = false;
        }
      }
      if(flag) {
        if(ret == -1 || cnt < ret) {
          ret = cnt;
        }
      }
    }
    printf("Case #%d: ",ca++);
    if(ret == -1) {
      puts("NOT POSSIBLE");
    } else {
      printf("%d\n",ret);
    }
  }
  return 0;
}

