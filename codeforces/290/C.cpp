#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
char s[110][110];
vector<int> edge[430];
int main()
{
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
                scanf("%s", s[i]);
        }
        int in[26];
        memset(in, 0, sizeof(in));
        for(int i = 0; i < n - 1; i ++) {
                int len1 = strlen(s[i]);
                int len2 = strlen(s[i + 1]);
                bool flag = true;
                for(int j = 0; j < min(len1, len2); j++) {
                        if(s[i][j] != s[i + 1][j]) {
                                edge[s[i][j]-'a'].push_back(s[i+1][j]-'a');
                                in[s[i+1][j] - 'a']++;
                                flag = false;
                                break;
                        }
                }
                if(flag) {
                        if(len1 > len2) {
                                puts("Impossible");
                                return 0;
                        }
                }
        }
        queue<int> Q;
        for(int i = 0; i < 26; i++) {
                if(in[i] == 0) {
                        Q.push(i);
                }
        }
        vector<char> res;
        while(!Q.empty()) {
                int fr = Q.front(); Q.pop();
                res.push_back('a' + fr);
                for(int i = 0; i < edge[fr].size(); i++) {
                        int to = edge[fr][i];
                        if((--in[to]) == 0) {
                                Q.push(to);
                        }
                }
        }
        if(res.size() != 26) puts("Impossible");
        else for(int i = 0; i < res.size(); i++)printf("%c", res[i]);
        return 0;
}
