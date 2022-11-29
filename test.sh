#!/usr/bin/env bash

set -o nounset

make
for (( i = 1; i <= 200; i += 3 )) do
  bin/gen "$i"
  for (( j = 1; j <= 6; j += 1 )) do
    printf "i = $i, j = $j\n"
    cat test/input.txt | bin/main "$j" > test/out.txt
    git diff --unified=0 --no-index test/out.txt test/output.txt
  done
done
printf "Done"