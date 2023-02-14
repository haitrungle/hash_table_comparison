# Hash table comparison

This project implements different hash tables and compare them. The two factors distinguishing each implmentation are

1. Hashing methods ("hasher" folder)
   - Modular (division) hashing
   - Multiplicative hashing
2. Collision resolution strategy ("hashtable" folder)
   - Separate chaining
   - Linear probing
   - Quadratic probing

Detailed comments about the implementation can be found in the `*.cpp` files under "hasher" and "hashtable" folders. 

## Compile and run benchmarks

Require `make` and `bash` (also works on WSL). To compile and benchmark implementation 1 (separate chaining, modular hashing):

```sh
make
./benchmark.sh 1
```

The "Report.pdf" file contains more details.