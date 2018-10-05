#include<cstdio>
#include<cstring>
typedef long long lld;
lld dp[30][3],ans;
//dp[i][0]: i位数不包含49
//dp[i][1]: 以9开头不包含49
//dp[i][2]: i位数包含49 
int num[30];
int main(){
    int i,j,k,t;
    unsigned __int64 n;
    dp[0][0]=1;
    for(i=1;i<=20;i++){
        dp[i][0]=dp[i-1][0]*10-dp[i-1][1]; //当前位取4,后一位取9的要减掉
        dp[i][1]=dp[i-1][0];
        dp[i][2]=dp[i-1][2]*10+dp[i-1][1];
    }
    scanf("%d",&t);
    while(t--){
        int tot=0;
        ans=0;
        scanf("%llu",&n);n++;
        while(n){
            num[++tot]=n%10;
            n/=10;
        }
        bool flag=false;
        int pre=0;
        for(i=tot;i>=1;i--){
            ans+=dp[i-1][2]*num[i];
            if(flag) ans+=dp[i-1][0]*num[i];
            else if(num[i]>4) ans+=dp[i-1][1];
            if(pre==4&&num[i]==9) flag=1;
            pre=num[i];
        }
        printf("%lld\n",ans);
        
    }
}

