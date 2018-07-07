#include <bits/stdc++.h>
using namespace std;


char TT(char ch) {
    if(ch >= 'a' && ch <= 'z') {
        return ch + 'A'-'a';
    }
    return ch;
}
char D(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch;
    }
    return ch + 'a'-'A';
}
int main () {
    int T;
    scanf("%d", &T);
        getchar();
    while(T--) {
        char s[22];
        gets(s);
        int n = strlen(s);
        vector<string> name;
        string tmp = "";
        for (int i = 0; i < n; i++) {
            if (s[i] == ' ') {
                name.push_back(tmp);
                tmp = "";
            } else {
                tmp += s[i];
            }
        }
        name.push_back(tmp);
        tmp = "";
        if((int) name.size() > 1) {
            for (int i = 0; i < (int)name.size() - 1; i++) {
                tmp += TT(name[i][0]);
                tmp += ". ";
            }
        } 
        tmp += TT(name[(int)name.size() - 1][0]);
        for (int i = 1; i < name[(int)name.size() - 1].length(); i++) {
            tmp += D(name[(int)name.size() - 1][i]);
        }
        cout << tmp << endl;
    }
    return 0;
}
