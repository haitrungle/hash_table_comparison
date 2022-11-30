#!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

if [[ "${1-}" =~ ^-*h(elp)?$ || "$#" -eq 0 ]]; then
    echo 'Usage: ./benchmark.sh X [NUM]

Run the benchmark, where X is a number indicating the hash table
implementation. The allowed values of X are:

    0 std::unordered_set, default hashing
    1 separate chaining, division hashing
    2 separate chaining, multiplicative hashing
    3 linear probing, division hashing
    4 linear probing, multiplicative hashing
    5 quadratic probing, division hashing
    6 quadratic probing, multiplicative hashing

The benchmark is ran NUM times, defaulting to 50.
'
    exit
fi

cd "$(dirname "$0")"

names=("std::unordered_set, default hashing", "separate chaining, division hashing" "separate chaining, multiplicative hashing" "linear probing, division hashing" "linear probing, multiplicative hashing" "quadratic probing, division hashing" "quadratic probing, multiplicative hashing")

X="$1"
NUM="${2:-50}"
TIMEFORMAT="total: %U+%S seconds"

make

bin/gen 191 50000 10000
for (( i=0; i<3; i+=1 )) do
    cat "test/input-$i.txt" | bin/main 0 > "test/output-$i.txt"
done

printf "\nBenchmarking ${names[X]}\n"
benchmark() {
    for (( try=0; try<NUM; try+=1 )) do
        cat "test/input-$1.txt" | bin/main "$X" > "test/out-$1.txt"
        if [[ try -eq 0 ]]; then
            git diff --unified=0 --no-index "test/out-$1.txt" "test/output-$1.txt"
        fi
    done
}
for (( i=0; i<3; i+=1 )) do
    printf "Input $i\n"
    time benchmark "$i"
    printf "\n"
done