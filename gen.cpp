#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Expected 3 arguments: seed, numOperations, and keyUpperBound\n";
        return 1;
    }

    const string OPTIONS[3] = {"search", "insert", "delete"};

    unsigned seed = atoi(argv[1]);
    unsigned numOperations = atoi(argv[2]);
    unsigned keyUpperBound = atoi(argv[3]);

    minstd_rand rng(seed);
    uniform_int_distribution<unsigned> valGen(0, keyUpperBound);
    discrete_distribution<unsigned> optGen({40, 40, 20}); // 40% search, 40% insert, 20% delete
    discrete_distribution<int> signGen({50, 50}); // 50% negative, 50% positive

    ofstream input0("test/input-0.txt");
    for (unsigned i = 0; i < numOperations; i++) {
        unsigned opt = optGen(rng);
        unsigned val = valGen(rng);
        input0 << OPTIONS[opt] << " " << val << "\n";
    }

    ofstream input1("test/input-1.txt");
    unsigned val = valGen(rng) * 2 + 1;
    for (unsigned i = 0; i < numOperations; i++) {
        unsigned opt = optGen(rng);
        unsigned sign = signGen(rng) * 2 - 1;
        input1 << OPTIONS[opt] << " " << (val + i*32) % keyUpperBound << "\n";
    }

    ofstream input2("test/input-2.txt");
    for (unsigned i = 0; i < numOperations; i++) {
        unsigned opt = optGen(rng);
        unsigned sign = signGen(rng) * 2 - 1;
        input2 << OPTIONS[opt] << " " << (val + i) % keyUpperBound << "\n";
    }

    return 0;
}