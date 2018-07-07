#include <cstdio>
#include <algorithm>
int main(){
  static int a[500010];
  int n,i;
  scanf("%d",&n);
  for(i = 0; i < n; i++) scanf("%d",&a[i]);
  std::sort(a,a+n);
  int j = n-1;
  int ans = 0;
  for(i = n/2-1; i >= 0; i--){
    if(j >= 0 && a[i]*2 <= a[j]){
      a[j] = -1;
      ans++;
      j--;
    }
    while(j>=0 && a[j]==-1) j--;
  }
  printf("%d\n",n-ans);
  return 0;
}
