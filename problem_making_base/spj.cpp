#include "testlib.h"
#include <iostream>
#include <fstream>
using namespace std;

string get_string(InStream &in) {
    string ret= "";
    while(ret == "")  {
        ret = in.readString();
    }
    return ret;
}

string get_line(InStream &in) {
    string ret = "";
    while(ret == "") {
        ret = in.readLine();
    }
    return ret;
}


int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n, m;
    n = inf.readInteger();
    m = inf.readInteger();
    int user_out = ouf.readInteger();
    int answer = ans.readInteger();
//    quitp(25);
//    quitf(_wa, "expected length %d, found length %d", n, cnt);
    return 0;
}
