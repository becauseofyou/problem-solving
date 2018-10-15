g++-6 gen.cpp -o gen
g++-6 std.cpp -o std
g++-6 brute.cpp -o brute
while true; do
    ./gen > data.in
    ./std < data.in > std.out
    ./brute <data.in > brute.out
    if diff std.out brute.out; then
        echo AC
    else
        echo WA
        cat std.out brute.out
        exit 0
    fi
done
