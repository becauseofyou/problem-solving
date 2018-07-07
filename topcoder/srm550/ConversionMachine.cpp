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

class ConversionMachine
{
public: 
    int countAll(string word1, string word2, vector <int> costs, int maxCost);
    
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "a"; string Arg1 = "b"; int Arr2[] = {100,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 205; int Arg4 = 2; verify_case(0, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arg0 = "abcba"; string Arg1 = "abcba"; int Arr2[] = {67,23,43}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; int Arg4 = 1; verify_case(1, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arg0 = "cccccccc"; string Arg1 = "aaaaaaaa"; int Arr2[] = {10000000,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 100; int Arg4 = 40320; verify_case(2, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arg0 = "aa"; string Arg1 = "cc"; int Arr2[] = {1,10,100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1787; int Arg4 = 123611681; verify_case(3, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
    ConversionMachine ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
const int mod = 1000000007;
int change[128][128];
void init(vector<int> cost) {
  change['a']['b'] = cost[0];
  change['b']['c'] = cost[1];
  change['c']['a'] = cost[2];
  change['a']['c'] = cost[0] + cost[1];
  change['b']['a'] = cost[1] + cost[2];
  change['c']['b'] = cost[2] + cost[0];
}
int mp[20][20][20];
int idx[100][3];
int trans[110][110];
const int SZ = 100;
int sz;
struct Matrix {
  int mat[SZ][SZ];
  Matrix(){
    memset(mat,0,sizeof(mat));
  }
  void init() {
    for(int i = 0; i < sz; i++) {
      mat[i][i] = 1;
    }
  }
  void print() {
    for(int i = 0; i < sz; i++) {
      for(int j = 0; j < sz; j++) {
        printf("%d ",mat[i][j]);
      }
      puts("");
    }
  }
};
Matrix operator * (Matrix &a, Matrix &b) {
  Matrix ret;  ret.init();
  for(int i = 0; i < sz; i++) {
    for(int j = 0; j < sz; j++) {
      long long sum = 0;
      for(int k = 0; k < sz; k++) {
        sum += (1LL * a.mat[i][k] * b.mat[k][j]) % mod; 
        if(sum >= mod) sum -= mod;
      }
      ret.mat[i][j] = (int)sum;
    }
  }
  return ret;
}
Matrix operator ^(Matrix &a,int k) {
  Matrix ret; ret.init();
  while(k > 0) {
    if(k & 1) ret = ret * a;
    k >>= 1; a = a * a;
  }
  return ret;
}
int ConversionMachine::countAll(string word1, string word2, vector <int> costs, int maxCost)
{
  init(costs);
  long long cost = 0, totStep = 0, cnt[3]; memset(cnt, 0, sizeof(cnt));
  for(int i = 0; i < (int) word1.size(); i++) {
    if(word1[i] != word2[i]) {
      cost += change[word1[i]][word2[i]];
      int pre = totStep;
      if(word2[i] > word1[i]) totStep += word2[i] - word1[i];
      else totStep += 'c' - word1[i] + 1 + word2[i] - 'a';
      cnt[totStep - pre] ++;
    }
    else cnt[0]++;
  }
  if(maxCost < cost) return 0;
  totStep += (maxCost - cost) / (costs[0] + costs[1] + costs[2]) * 3;
  int n = (int)word1.size();
  sz = 0;
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j <= n; j++) {
      for(int k = 0; k <= n; k++) if(i + j + k == n){
        mp[i][j][k] = sz;
        idx[sz][0] = i;
        idx[sz][1] = j;
        idx[sz][2] = k;
        sz++;
      }
    }
  }
  sz ++;
  Matrix trans;
  for(int i = 0; i < sz - 1; i++) {
    int a = idx[i][0], b = idx[i][1], c = idx[i][2], to;
    if(a) {
      int cc = c + 1;
      to = mp[a-1][b][cc];
      trans.mat[i][to] += a;
    }  if(b){
      int aa = a + 1;
      to = mp[aa][b-1][c];
      trans.mat[i][to] += b;
    }  if(c) {
      int bb = b + 1;
      to = mp[a][bb][c-1];
      trans.mat[i][to] += c;
    }
  }
  trans.mat[sz-1][sz-1] = 1;
  trans.mat[sz-1][mp[cnt[0]][cnt[1]][cnt[2]]] = 1;
  trans = trans ^ (totStep + 1) ;
  return trans.mat[sz-1][mp[n][0][0]];
}
