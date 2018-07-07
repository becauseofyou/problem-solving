@echo off         
for /l %%i in (0,1,9) do fc data%%i.out cmp%%i.out