#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>
#include <iostream>
using namespace std;

int cnt[11];
set<string> st;
char s[1111];
set<string> par;

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        st.clear(); par.clear();
        int tot = 0, ans = 0;
        for(int i = 1;i <= 4; i++)  cnt[i] = 0;
        for(int i = 0;i < n; i++){
            scanf("%s", s);
            int len = strlen(s);
            int id = -1;
            for(int j = 0;j < len; j++) if(s[j] == ':') {
                id = j;
                break;
            }
            bool fuck = true;
            if(id+2 != len || !(s[id+1]>='1' && s[id+1]<='4')) {
                fuck = false;
            }
            int vote = s[id+1]-'0';
            string cur;
            if(s[0] == '+') {
                for(int j = 0;j < id; j++) if(s[j]>='0' && s[j]<='9')
                    cur += s[j];
            }
            else if(s[0] >= '1' && s[0] <= '9'){
                cur += "9821";
                for(int j = 0;j < id; j++) if(s[j]>='0'&&s[j]<='9')
                    cur += s[j];
            }
            else {
                cur += "98";
                for(int j = 1;j < id; j++) if(s[j] >= '0' && s[j] <= '9')
                    cur += s[j];
            }
            //cout<<"cur = "<<cur<<endl;
            par.insert(cur);
            if(!st.count(cur) && fuck) {
                st.insert(cur);
                cnt[vote]++;
                tot++;
            }
        }
        for(int i= 1;i <= 4; i++) {
            int cur = (int)((double)cnt[i]/tot*100);
            printf("%d", cur);
            puts("%");
        }
        printf("Participants:%d\n", par.size());
    }
    return 0;
}