/*

SOURCE

    https://leetcode.com/problems/count-of-smaller-numbers-after-self/
    

EXPLANATION

    For each number, the count of smaller numbers after self is the count
    of the numbers that would be transferred from its right to its left
    when sorting the array. Therefore, we sort the array (using mergeSort)
    and calculating counts at the same time.

    We split the array into two halves, left and right, recursively sort them 
    and in the process calculate counts (of smaller elements to the right)
    for numbers in each half. For each number in the left half, we need to
    increase its count by the count of smaller elements that belong to the 
    right half. This can be done through the merge operation.

    The merge operation merges two halves that are already sorted into one.
    Inside merge, each time when adding a number from the left half to the 
    temporary cache (used to overwrite the values in the original array in 
    correct order), we increase that number's count by the count of numbers 
    that have already been written into the cache from the right half.


TIME COMPLEXITY

    T(n) = O(n logn)

    MergeSort works in O(n logn) time as it recursively splits the array 
    into two equal halves resulting in logn levels in a recursion tree. 
    At each level linear time, O(n), is needed to combine the two halves 
    using the merge operation.


SPACE COMPLEXITY

    S(n) = O(n)

    The merge operation uses a temporary cache of size O(n). 

*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class Solution {
private:
    void mergeWithInversionsCounts(
        vector<std::pair<int, size_t>>& valsAndInds,
        vector<std::pair<int, size_t>>& cache,
        size_t left,
        size_t right,
        vector<int>& counts
    ) {
        size_t mid = left + (right - left) / 2;   

        size_t ind1{ left };
        size_t ind2{ mid };
        
        for (size_t ind{ left }; ind < right; ++ind) {
            if (ind1 == mid) {
                cache[ind] = valsAndInds[ind2++];
            } else if (ind2 == right) {
                counts[ valsAndInds[ind1].second ] += (ind2 - mid);
                cache[ind] = valsAndInds[ind1++];
            } else if (valsAndInds[ind1].first <= valsAndInds[ind2].first) {
                counts[ valsAndInds[ind1].second ] += (ind2 - mid);
                cache[ind] = valsAndInds[ind1++];
            } else {
                cache[ind] = valsAndInds[ind2++];
            }
        }
    
        for (size_t ind{ left }; ind < right; ++ind)
            valsAndInds[ind] = cache[ind];
    }

    void mergeSortWithInversionCounts(
        vector<std::pair<int, size_t>>& valsAndInds,
        vector<std::pair<int, size_t>>& cache,
        size_t left,
        size_t right,
        vector<int>& counts
    ) {
        if (right <= left + 1)
            return;
        
        size_t mid = left + (right - left) / 2;   
        mergeSortWithInversionCounts(valsAndInds, cache, left, mid, counts);
        mergeSortWithInversionCounts(valsAndInds, cache, mid, right, counts);

        mergeWithInversionsCounts(valsAndInds, cache, left, right, counts);
    }
    
public:
    vector<int> countSmaller(vector<int>& nums) {
        
        vector<std::pair<int, size_t>> valsAndInds(nums.size());
        for (size_t i{ 0 }; i < nums.size(); ++i) 
            valsAndInds[i] = std::pair<int, size_t>{ nums[i], i };
        
        vector<std::pair<int, size_t>> cache(valsAndInds.size());        
        vector<int> counts(nums.size(), 0);

        mergeSortWithInversionCounts(valsAndInds, cache, 0, valsAndInds.size(), counts);

        return counts;
    }
};

int main() {
    vector<int> nums{ 5, 2, 6, 1 };
    Solution s{};
    vector<int> counts{ s.countSmaller(nums) };

    for (size_t i{ 0 }; i < nums.size(); ++i)
        std::cout << nums[i] << ' ' << counts[i] << '\n';
}
