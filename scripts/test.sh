#!/bin/bash

INPUT_NAME=input
OUTPUT_NAME=output
MY_NAME=my_output
cppfile=noname.cpp

if ! g++ -g  -Wall $1 -std=c++11; then
    exit
fi

#删除所有用户输出而且不显示错误信息 
rm -R $MY_NAME* 2>/dev/null

all=0
passed=0
for test_file in $INPUT_NAME*
do
    all=$(($all+1))
    #去除INPUT_NAME前缀
    i=${#INPUT_NAME} 
    test_case=${test_file:$i}
    if ! ./a.out < $INPUT_NAME$test_case > $MY_NAME$test_case; then
        echo -e "\033[31mSample test \#$test_case: Runtime Error \033[0m"
        echo ========================================
        echo Sample Input \#$test_case
        cat $INPUT_NAME$test_case
    else
        if diff --brief $MY_NAME$test_case $OUTPUT_NAME$test_case; then
            echo -e "\033[42;30mSample test #$test_case: Passed \033[0m"
			passed=$(($passed+1))
        else
            echo -e "\033[41;30mSample test #$test_case: failed \033[0m"
            echo ========================================
            echo Sample Input \#$test_case
            cat $INPUT_NAME$test_case
            echo ========================================
            echo Sample Output \#$test_case
            cat $OUTPUT_NAME$test_case
            echo ========================================
            echo My Output \#$test_case
            cat $MY_NAME$test_case
            echo ========================================
            echo -e
        fi
    fi
done
if (($all == $passed)); then
    echo -e "\033[42;30m Successfully Passed All the $all tests \033[0m"
else
    echo -e  "\033[43;34m $all cases，passed $passed，failed $(($all-$passed)) \033[0m" 
fi
