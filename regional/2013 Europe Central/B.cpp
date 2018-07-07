#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <map>
using namespace std;
string str;
vector<string> res, voice;
map<string, int> mp;
int main() {
        int T;
        string tmp;
        getline(cin , tmp);
        istringstream istr(tmp);
        istr >> T;
        while(T--) {
                res.clear();
                mp.clear();
                voice.clear();
                getline(cin, str);
                istringstream istr(str);
                string tmp ;
                while(istr >> tmp) {
                        voice.push_back(tmp);
                }
                while(true) {
                        getline(cin, str);
                        istringstream istr(str);
                        int cnt = 0;
                        while(istr >> tmp) {
                                cnt ++;
                                //
                        }
                        if(cnt == 3) {
                                mp[tmp] = 1;
                        } else break;

                }
                for(int i = 0; i < voice.size(); i++) {
                        if(mp.find(voice[i]) == mp.end()) {
                                res.push_back(voice[i]);
                        }
                }
                for(int i = 0; i < res.size(); i++) {
                        if(i) cout << " " ;
                        cout<< res[i];
                }
                cout << endl;
        }
        return 0;
}