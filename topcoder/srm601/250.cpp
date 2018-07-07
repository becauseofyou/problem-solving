#line 2 "WinterAndPresents.cpp"
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


class WinterAndPresents
{
        public:
        long long getNumber(vector <int> apple, vector <int> orange);
        

};
long long  WinterAndPresents :: getNumber(vector <int> apple, vector <int> orange)
{
      long long ans = 0;
      int mi = 2000000, mx = 0;
      for(int i = 0; i < apple.size(); i++) {
        int t = apple[i] + orange[i];
        if(t > mx) mx = t;
        if(t < mi) mi = t;
      }
      for(int i = 1; i <= mi; i++) {
        int a = 0, b = 0;
        for(int j = 0; j < apple.size(); j++) {
          a += min(i,apple[j]);
          b += max(0,i - orange[j]);
        }
        ans += a - b + 1;
      }
      return ans;
}


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

