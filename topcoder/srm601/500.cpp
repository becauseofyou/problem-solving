#line 2 "WinterAndSnowmen.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;
const int inf = ~0u>>2;
#define PB push_back
#define MP make_pair
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long LL;


class WinterAndSnowmen
{
        public:
        int getNumber(int N, int M);
        

};
const int md = 1000000007;
int f[2001][2048][2];
inline void Add(int &x,int y) {
  x += y;
  if(x >= md) x -= md;
}
int  WinterAndSnowmen :: getNumber(int N, int M)
{
  int n = max(N, M);
  int ret = 0;
  for(int r = 10; r >= 0; r--) {
    memset(f,0,sizeof(f));
    f[0][0][0] = 1;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < 2048; j++) {
        for(int k = 0; k < 2; k++) {
          Add(f[i + 1][j][k], f[i][j][k]); // do not put number i + 1
          if(i + 1 <= N)  // put i + 1 to the Aset
            Add(f[i + 1][j ^ (i + 1)][((i + 1) >> r & 1) ^ k], f[i][j][k]);
          if(i + 1 <= M)  // put i + 1 to the Bset
            Add(f[i + 1][j ^ (i + 1)][k], f[i][j][k]);
        }
      }
    }
    for(int j = 1 << r; j < (1 << (r + 1)); j++) 
      Add(ret, f[n][j][0]);
  }
  return ret;
}


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
