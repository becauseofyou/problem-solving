#!/bin/bash
g++ xj3757.cpp -o my

file='*.in'
i=1
for item in $file
do
    filename=${item%.*}
    echo -e "\033[33m running on test $i... \033[0m"
    /usr/bin/time -f %U ./my < $item > my$i.ans 2>tmp
    tm=`cat tmp`
    rm tmp
    if diff my$i.ans $filename.out; then
        echo -e -n "\033[33m Example $i... \033[0m"
        echo -e "\033[32m PASSED   Time: $tm s\033[0m"
        rm my$i.ans
    else
        echo -e -n "\033[33m Example $i... \033[0m"
        echo -e "\033[31m FAILED\033[0m"
    fi
    i=$(($i+1))
    echo -e
done
