#include <cstdio>
#include <iostream>
#include <cstring>
long long ret;
void gcd(long long a, long long b) {
    if(a == 1) {
        ret += b;
        return ;
    }
    ret += a / b;
    gcd(b, a % b);
}
int main() {
    long long a, b;
    std::cin>>a>>b;
    gcd(a, b);
    std::cout<<ret<<std::endl;
    return 0;
}

