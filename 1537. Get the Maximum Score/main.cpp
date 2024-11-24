/*

SOURCE

    https://leetcode.com/problems/get-the-maximum-score/
    

ALGORITHM

    We break the two input arrays into subarrays ending in common values and 
    consider such pairs of subarrays (one from each input array) separately. 
    From each pair, we choose the subarray with the larger score.


PROOF OF CORRECTNESS

    We prove that the path that is built by the greedy strategy of choosing a subarray 
    with a greater score from each pair of subarrays (one from each input array) ending
    in a common value maximizes the score by comparing such a path with some optimal
    path.

    Since we are allowed to change the path to another array only at the end of a 
    subarray ending in a common value, the optimal path neceserily consists of a 
    series of such subarrays. When building our subarray, at each pair of subarrays
    ending in a common value, if the optimal path includes the one with a higher
    score, then we can do so as well and move on to the next pair. If the optimal
    path does not include the subarray with a higher score, we can actually improve
    on it by selecting the said subarray. This will increase our score and will 
    not affect the selection of subsequent subarrays.

    Thus, selecting the subarray with a higher score from each pair of subarrays
    ending in a common value will always be consistent with an optimal path maximizing
    the score.
     

TIME COMPLEXITY

    T(n) = O(n)

    Since only one pass through each of the arrays is required, the
    time complexity is linear.     


SPACE COMPLEXITY

    S(n) = O(1)

*/

#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    int maxSum(std::vector<int>& nums1, std::vector<int>& nums2) {
        long base = 1000000007;

        long max = 0;
        int i = 0, j = 0;
        long cum1 = 0, cum2 = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                max = (max + ( std::max(cum1, cum2) + nums1[i] ) % base) % base;
                cum1 = cum2 = 0;
                ++i;
                ++j;
            } else if (nums1[i] < nums2[j]) {
                cum1 += nums1[i];
                ++i;
            } else {
                cum2 += nums2[j];
                ++j;
            }
        }

        while (i < nums1.size()) {
            cum1 += nums1[i];
            ++i;
        }
        while (j < nums2.size()) {
            cum2 += nums2[j];
            ++j;
        }
        
        max = (max + std::max(cum1, cum2)) % base;
        return max; 
    }
};

int main() {
    std::vector<int> nums1{ 2,4,5,8,10 };
    std::vector<int> nums2{ 4,6,8,9 };
    Solution s{};
    int res{ s.maxSum(nums1, nums2) };
    std::cout << res << '\n';
}