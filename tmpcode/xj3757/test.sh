#!/bin/bash

INPUT_NAME=input
OUTPUT_NAME=output
MY_NAME=my_output

if ! g++-6 -g  -Wall std.cpp; then
    exit
fi

#删除所有用户输出而且不显示错误信息 
rm -R $MY_NAME* 2>/dev/null


for test_file in $INPUT_NAME*
do
    #去除INPUT_NAME前缀
    i=${#INPUT_NAME} 
    test_case=${test_file:$i}
    if ! ./a.out < $INPUT_NAME$test_case > $MY_NAME$test_case; then
        echo [1m[31mSample test \#$test_case: Runtime Error[0m 
        echo ========================================
        echo Sample Input \#$test_case
        cat $INPUT_NAME$test_case
    else
        if diff --brief $MY_NAME$test_case $OUTPUT_NAME$test_case; then
            echo [1m[32mSample test \#$test_case: Accepted[0m 
        else
            echo [1m[31mSample test \#$test_case: Wrong Answer[0m 
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
        fi
    fi
done
