#!/usr/bin/env bash

set -o nounset

make

for (( seed = 1; seed <= 200; seed += 10 )) do
    bin/gen "$seed" 50000 10000
    printf "==== seed = $seed ====\n"
    for (( i=0; i<4; i+=1 )) do
        cat "test/input-$i.txt" | bin/main 0 > "test/output-$i.txt"
    done

    for (( j = 1; j <= 6; j += 1 )) do
        for (( i=0; i<4; i+=1 )) do
            cat "test/input-$i.txt" | bin/main "$j" > "test/out-$i.txt"
            git diff --unified=0 --no-index "test/out-$i.txt" "test/output-$i.txt"
            if [[ i -eq 2 ]]; then printf "j = $j\n"; fi
        done
    done
done
printf "Done\n"