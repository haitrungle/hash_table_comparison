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

The benchmark is ran NUM times, defaulting to 10.
'
    exit
fi

cd "$(dirname "$0")"

names=("std::unordered_set, default hashing", "separate chaining, division hashing" "separate chaining, multiplicative hashing" "linear probing, division hashing" "linear probing, multiplicative hashing" "quadratic probing, division hashing" "quadratic probing, multiplicative hashing")

X="$1"
NUM="${2:-10}"
sum=""

make
printf "Benchmarking ${names[X]}\n"
for (( i = 1; i <= NUM; i += 1 )) do
    bin/gen "$(($i*3 + 181))"

    start_time="$(date -u +%s.%N)"
    cat test/input.txt | bin/main "$X" > test/out.txt
    end_time="$(date -u +%s.%N)"

    secs="$(bc <<<"$end_time-$start_time")"
    sum+="$secs + "
    printf "Run $i: $secs seconds\n"

    git diff --unified=0 --no-index test/out.txt test/output.txt
done
sum+="0"
elapsed="$(bc <<<"$sum")"
echo "Total: $elapsed seconds"