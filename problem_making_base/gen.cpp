// https://github.com/MikeMirzayanov/testlib/tree/master/generators
#include "testlib.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int main (int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    for (int test = 0; test < 10; test++) {
        startTest(test);
        cout << rnd.next(1, 100) << endl;
    }
    return 0;
}
