#line 2 "ORSolitaire.cpp"
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


class ORSolitaire
{
        public:
        int getMinimum(vector <int> numbers, int goal);
        

};
int  ORSolitaire :: getMinimum(vector <int> number, int goal)
{
  int s = 0;
  int a[33];memset(a,0,sizeof(a));
  for(int i = 0; i < (int)number.size(); i++) {
    if((number[i]&goal) == number[i]) {
      s |= number[i];
      for(int j = 0; j <= 30; j++) if(number[i]&(1<<j)){
        a[j] ++;
      }
    }
  }
  if(s != goal) return 0;
  else {
    int mi = 10000;
    for(int i = 0; i <=30; i++) if(a[i])mi = min(mi,a[i]);
    return mi;
  }
}


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor