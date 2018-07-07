/* **********************************************
Author      : wuyiqi
Created Time: 2014��04��06�� ������ 20ʱ47��51��
File Name   : D.cpp
*********************************************** */
#include <set>
#include <map>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
#include <deque>
#include <bitset>
#include <cstdio>
#include <vector>
#include <string>
#include <complex>
#include <sstream>
#include <utility>
#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
int main() {
    std::string s;
    std::cin>>s;
    std::stack<char> stack;
    for(int i = 0; i < s.length(); i++) {
        bool poped = false;
        while(stack.size() > 0 && s[i] == stack.top()) {
            poped = true;
            stack.pop();
        }
        if(!poped) {
            stack.push(s[i]);
        }
    }
    if(!stack.empty()) {
        puts("No");
    } else {
        puts("Yes");
    }
    return 0;
}

