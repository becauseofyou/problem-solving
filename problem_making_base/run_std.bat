@echo off
set file_name=std
g++ -std=c++11 %file_name%.cpp -o %file_name%.exe -O2
for /l %%i in (0,1,9) do %file_name%.exe < data%%i.in > data%%i.out
