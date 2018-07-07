#include<iostream>
#include<map>
using namespace std;
string a[10001];
int b[10001];
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    map<string,int> mapp;
    for(int i=1;i<=k;i++){
        string s1;
        int s2;
        cin>>s1>>s2;
        mapp[s1]=s2;
    }
    long long ans=0;
    for(int i = 1; i <= n; i++) {
        if(mapp.find(a[i]) == mapp.end()) {
            cout<<"Unknow";
            return 0;
        } else {
            ans+=1LL * b[i] * mapp[a[i]];
        }
    }
    cout<<ans;
    return 0;
}
