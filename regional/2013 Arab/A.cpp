#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;
vector<int> pos[26];
int main() {
        int t;
        cin >> t;
        string s;
        while(t--) {
                cin >> s;
                int n = s.length();
                for(int i = 0; i < 26; i++) pos[i].clear();
                for(int i = 0; s[i]; i++)if(s[i] != '?') {
                        pos[s[i] - 'a'].push_back(i);
                }
                for(int i = 0; i < 26; i++)if(pos[i].size()) {
                        sort(pos[i].begin(), pos[i].end());
                }
                for(int i = 0; i < 26; i++) if(pos[i].size()) {
                        int start = pos[i].front();
                        int end = pos[i].back();
                        for(int j = start; j <= end; j++) {
                                s[j] = i + 'a';
                        }
                }
                long long ret = 1;
                for(int i = 0; s[i]; i++) {
                        if(s[i] == '?') {
                                int start = i;
                                while(s[i] && s[i] == '?')  {
                                        i++;
                                }
                                if(start == 0 || !s[i]) {
                                        // do nothing
                                }
                                else {
                                        ret = ret * (i - start + 1) % MOD; 
                                }
                                i --;
                        } else {
                                // do nothing
                        }
                }
                printf("%d\n",(int)ret);
        }
        return 0;
}