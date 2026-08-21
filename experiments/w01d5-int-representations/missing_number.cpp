#include <algorithm>
#include <cstdio>
#include <vector>

int missingNumberGaussNaive(const std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    int expected = n * (n + 1) / 2;
    int actual = 0;
    for (int x : nums) actual += x;
    return expected - actual;
}

int missingNumberGaussSafe(const std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    int expected = (n % 2 == 0) ? (n / 2) * (n + 1) : n * ((n + 1) / 2);
    int actual = 0;
    for (int x : nums) actual += x;
    return expected - actual;
}

int missingNumberXor(const std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    int result = n;
    for (int i = 0; i < n; ++i) result ^= i ^ nums[i];
    return result;
}

int missingNumberSort(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    for (std::size_t i = 0; i < nums.size(); ++i)
        if (nums[i] != static_cast<int>(i)) return static_cast<int>(i);
    return static_cast<int>(nums.size());
}

int main() {
    const int n = 46341;
    std::vector<int> nums;
    nums.reserve(n);
    for (int i = 0; i < n; ++i) nums.push_back(i);
    const int missing = n;

    std::printf("n = %d (naive n*(n+1) = %lld, overflows 32-bit int)\n", n,
                static_cast<long long>(n) * (n + 1));
    std::printf("gauss naive = %d\n", missingNumberGaussNaive(nums));
    std::printf("gauss safe  = %d\n", missingNumberGaussSafe(nums));
    std::printf("xor         = %d\n", missingNumberXor(nums));
    std::printf("sort        = %d\n", missingNumberSort(nums));
    std::printf("expected missing = %d\n", missing);
    return 0;
}
