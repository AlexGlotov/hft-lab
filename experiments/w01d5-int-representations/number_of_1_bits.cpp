#include <bit>
#include <cstdint>
#include <cstdio>

int hammingWeightNaive(uint32_t n, int& iterations) {
    int count = 0;
    iterations = 0;
    while (n) {
        count += n & 1u;
        n >>= 1;
        ++iterations;
    }
    return count;
}

int hammingWeightKernighan(uint32_t n, int& iterations) {
    int count = 0;
    iterations = 0;
    while (n) {
        n &= n - 1u;
        ++count;
        ++iterations;
    }
    return count;
}

void report(uint32_t n) {
    int iterNaive = 0, iterKernighan = 0;
    int cNaive = hammingWeightNaive(n, iterNaive);
    int cKernighan = hammingWeightKernighan(n, iterKernighan);
    int cStd = std::popcount(n);
    std::printf("n = 0x%08X: naive=%d (%d iter), kernighan=%d (%d iter), std::popcount=%d\n",
                n, cNaive, iterNaive, cKernighan, iterKernighan, cStd);
}

int main() {
    report(1u);
    report(0x80000000u);
    report(0b10110000u);
    return 0;
}
