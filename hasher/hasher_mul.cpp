#pragma once
#include "hasher.h"
/*
    Hasher_Mul: multiplicative hashing

    Given the table size m and an integer x, the hash value is

        h(x) = floor(m * {x*a}),

    where a is a real number and {x*a} = x*a - floor(x*a) is the fractional
    part of x*a. Since floating-point operations are slow, we can instead
    calculate this as

        h(x) = floor(m * (x * A / 2^w)),

    where A is a large integer. If the table size is a power of two 2^p (as
    it usually is), this can be simplified to 

        h(x) = floor(x * A / 2^(w - p)) = x * A >> (w - p),

    which is very fast to compute.

    The problem of which constant A to choose has been studied extensively,
    and Knuth reccomends A such that a = A / 2^w is close to the inverse of
    the golden ratio, (sqrt(5)-1) / 2. See "The Art of Computer Programming,
    Volume 3" by Knuth, section 6.4, page 516-517.
*/

struct Hasher_Mul : Hasher {
    unsigned hash(unsigned x) {
        return (x * A) >> (32 - p);
    }
    void set_size(unsigned size) {
        table_size = size;
        int power = 0;
        while (size >> power) ++power;
        p = power - 1;
    }

private:
    unsigned table_size;
    unsigned p; // = floor(log2(table_size))
    const static unsigned A = 2654435769; // = 2^32 * (sqrt(5)-1)/2
};