@echo off
for /l %%i in (0,1,9) do python D.py < data%%i.in > cmp%%i.out
