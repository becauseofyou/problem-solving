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
#include <ctime>
using namespace std;

class PalindromeMatrix
{
  public: 
    int minChange(vector <string> A, int rowCount, int columnCount);


    // BEGIN CUT HERE
  public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
  private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { string Arr0[] =
      {"0000"
      ,"1000"
      ,"1111"
      ,"1111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 4; int Arg3 = 7; verify_case(0, Arg3, minChange(Arg0, Arg1, Arg2)); }
    void test_case_1() { string Arr0[] = {"0000"
      ,"1000"
        ,"1100"
        ,"1110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; int Arg3 = 3; verify_case(1, Arg3, minChange(Arg0, Arg1, Arg2)); }
    void test_case_2() { string Arr0[] = {"01"
      ,"10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; verify_case(2, Arg3, minChange(Arg0, Arg1, Arg2)); }
    void test_case_3() { string Arr0[] = {"1110"
      ,"0001"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; verify_case(3, Arg3, minChange(Arg0, Arg1, Arg2)); }
    void test_case_4() { string Arr0[] =
        {"01010101"
        ,"01010101"
        ,"01010101"
        ,"01010101"
        ,"01010101"
        ,"01010101"
        ,"01010101"
        ,"01010101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 8; verify_case(4, Arg3, minChange(Arg0, Arg1, Arg2)); }
    void test_case_5() { string Arr0[] = {"000000000000"
      ,"011101110111"
        ,"010001010101"
        ,"010001010101"
        ,"011101010101"
        ,"010101010101"
        ,"010101010101"
        ,"011101110111"
        ,"000000000000"
        ,"000000000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 9; int Arg3 = 14; verify_case(5, Arg3, minChange(Arg0, Arg1, Arg2)); }
    void test_case_6() { string Arr0[] = {"11111101001110"
      ,"11000111111111"
        ,"00010101111001"
        ,"10110000111111"
        ,"10000011010010"
        ,"10001101101101"
        ,"00101010000001"
        ,"10111010100100"
        ,"11010011110111"
        ,"11100010110110"
        ,"00100101010100"
        ,"01001011001000"
        ,"01010001111010"
        ,"10100000010011"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 8; int Arg3 = 31; verify_case(6, Arg3, minChange(Arg0, Arg1, Arg2)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main()
{
  PalindromeMatrix ___test;
  ___test.run_test(-1);
  return 0;
}
// END CUT HERE

int n,m;
bool chsrow[15];
int ans;
int dp[10][16];
int needrow,needcol;
vector<string> B;
inline void update(int &x,int y) {
  if(x == -1 || y < x) x = y;
}
inline int getcost(int row1,int row2,int c1,int c2,char a,char b) {
  int ret = 0;
  ret += (B[row1][c1] != a);
  ret += (B[row1][c2] != b);
  ret += (B[row2][c1] != a);
  ret += (B[row2][c2] != b);
  return ret;
}
inline void checkmin(int &x,int y) {
  if(y < x) x = y;
}
inline int gao(int a,int b,char ch) {
  return B[a][b] != ch;
}
int solve() {
  for(int i = 0; i <= m / 2; i++) {
    for(int j = 0; j <= 2 * i; j++) {
      dp[i][j] = -1;
    }
  }
  dp[0][0] = 0;
  for(int col = 0; col < m / 2; col ++) {
    for(int has = 0; has <= 2 * col && has <= needcol; has ++) if(~dp[col][has]){
#ifndef debug
      //不管
      int cost = 0;
      for(int i = 0; i < n / 2; i++) {
        if(chsrow[i] && B[i][col] != B[i][m - 1 - col]) cost++;
        if(chsrow[n - 1 - i] && B[n - 1 - i][col] != B[n - 1 - i][m - 1 - col]) cost ++;
      }
      update(dp[col+1][has], dp[col][has] + cost);

      //把两列都变成回文
      cost = 0;
      for(int i = 0; i < n / 2; i++) {
        int tmp = 1000000;
        // 第i行放0 1
        if(!chsrow[i] && !chsrow[n - 1 - i]) {
          checkmin(tmp, getcost(i, n - 1 - i, col, m - 1 - col, '0', '1'));
        }
        // 第i行放1 0
        if(!chsrow[i] && !chsrow[n - 1 - i]) {
          checkmin(tmp, getcost(i, n - 1 - i, col, m - 1 - col, '1', '0'));
        }
        // 第i行放0 0
        checkmin(tmp,   getcost(i, n - 1 - i, col, m - 1 - col, '0', '0'));
        // 第i行放1 1
        checkmin(tmp,   getcost(i, n - 1 - i, col, m - 1 - col, '1', '1'));
        cost += tmp;
      }
      update(dp[col + 1][has + 2], dp[col][has] + cost);
      cost = 0;

      //把左边那列变成回文
      for(int i = 0; i < n / 2; i++) {
        int tmp = 1000000, s = 0;
        //第i行左边那列放0
        s += gao(i, col, '0');
        if(chsrow[i]) 
          s += gao(i, m - 1 - col, '0');

        s += gao(n - 1 - i, col, '0');
        if(chsrow[n - 1 - i]) 
          s += gao(n - 1 - i, m - 1 - col, '0');


        if(s < tmp) tmp = s;
        s = 0;
        //第i行左边那列放1
        s += gao(i, col, '1');
        if(chsrow[i]) 
          s += gao(i, m - 1 - col, '1');

        s += gao(n - 1 - i, col, '1');
        if(chsrow[n - 1 - i]) 
          s += gao(n - 1 - i, m - 1 - col, '1');

        if(s < tmp) tmp = s;
        cost += tmp;
      }
      update(dp[col + 1][has + 1], dp[col][has] + cost);
      cost  = 0;

      //把右边那列变成回文
      for(int i = 0; i < n / 2; i++) {
        int tmp = 1000000, s = 0;

        //第i行右边那列放0
        s += gao(i, m - 1 - col, '0');
        if(chsrow[i])
          s += gao(i, col, '0');

        s += gao(n - 1 - i, m - 1 - col, '0');
        if(chsrow[n - 1 - i]) 
          s += gao(n - 1 - i, col, '0');

        if(s < tmp) tmp = s;
        s = 0;

        //第i行右边那列放1
        s += gao(i, m - 1 - col, '1');
        if(chsrow[i]) 
          s += gao(i, col, '1');

        s += gao(n - 1 - i, m - 1 - col, '1');
        if(chsrow[n - 1 - i]) 
          s += gao(n - 1 - i, col, '1');

        if(s < tmp) tmp = s;
        cost += tmp;
      }
      update(dp[col + 1][has + 1], dp[col][has] + cost);
#endif
    }
  }
  return dp[m / 2][needcol];
}

void dfs(int dep,int cnt) {
  if(n - dep + cnt < needrow) return ;
  if(dep == n) {
    if(cnt != needrow) return ;
    int tmp = solve();
    if(tmp < ans) ans = tmp;
    return ;
  }
  chsrow[dep] = true;
  dfs(dep+1,cnt+1);
  chsrow[dep] = false;
  dfs(dep+1,cnt);
}

int PalindromeMatrix::minChange(vector <string> A, int rowCount, int columnCount)
{ 
  B = A;
  needrow = rowCount;
  needcol = columnCount;
  ans = 15 * 15;
  n = A.size(); m = A[0].length();
  dfs(0,0);
  return ans;
}
