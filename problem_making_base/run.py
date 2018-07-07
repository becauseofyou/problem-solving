import os
import time
from sys import argv

if __name__ == '__main__':
	os.system("g++-4.9 gen.cpp -o gen -O2 && ./gen && g++-4.9 std.cpp  -std=c++11 -o std && python3 run_std.py")
