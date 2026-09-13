#!/bin/bash

# 1. g++ a.cpp -o main
# 2. g++ b.cpp -o naive
# 3. ./test.sh

wa=0
cnt=0

while true
do
    cnt=$((cnt + 1))

    python3 gen.py > in.txt

    ./main < in.txt > out1.txt
    ./naive < in.txt > out2.txt

    if ! diff out1.txt out2.txt > /dev/null; then
        wa=$((wa + 1))

        echo -e "\033[31mWA\033[0m $cnt"
        echo "input:"
        cat in.txt
        echo "wrong answer:"
        cat out1.txt
        echo "correct answer:"
        cat out2.txt

        if [ $wa -ge 3 ]; then
            break
        fi
    else
        echo -e "\033[32mAC\033[0m $cnt"
    fi
done
