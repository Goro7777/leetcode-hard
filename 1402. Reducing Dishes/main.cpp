/*

SOURCE

    https://leetcode.com/problems/reducing-dishes/
    

KEY IDEAS

    To achieve a maximum sum, we should include in the mix all the dishes with 
    nonnegative satisfaction levels in ascending order. If there is such a dish 
    missing from the mix, the total will only increase with its inclusion (unless 
    all such dishes have a satisfaction level of 0, in which case the total will 
    stay at 0). If such dishes are not ordered in the ascending order, the total 
    can only get larger if an ascending order is adopted as higher values will
    receive higher times/weights.

    It is possible to include one or more dishes with negative satisfaction levels,
    This can increase the time/weight of the nonnegative dishes, positively affecting
    the total, so the inclusion of all such dishes should be checked. By the same 
    logic as before, negative dishes should be included in descending order so that
    those with larger absolute values receive lower times/weights.


ALGORITHM

    Sort the dishes in ascending order.

    Calculate the sum of all nonnegative dishes, in ascending order, as the 
    initial value of the total sum. 

    Progressively add negative dishes to the mix in descending order each time
    updating the total. 

    Return the total sum.

TIME COMPLEXITY

    T(n) = O(n logn)

    The most expensive operation is sorting. Since it is based on comparisons
    (of satisfaction levels), a time of O(n logn) can be assumed. 

    The calculation of all possible maximum totals can be done in linear time.
    Calculating the ordered sum of nonnegative dishes is trivial. After that, 
    for each negative dish we add to the mix, the new total can be calculated
    in constant time. The reason is that the differences between successive 
    totals change only by the satisfaction level of the new dish. For example, 
    if we have dishes with satisfaction levels: z, y, x, a, b, c with 
    z < y < x < 0 < a < b < c,
    The nonnegative total is:        a + 2b + 3c
    Add x. New total:           x + 2a + 3b + 4c    Difference:         x + a + b + c
    Add y. New total:      y + 2x + 3b + 4b + 5c    Difference:     y + x + a + b + c
    Add z. New total: z + 2y + 3x + 4b + 5c + 6d    Difference: z + y + x + a + b + c

    Thus, T(n) = O(n logn) + O(n) = O(n logn).


SPACE COMPLEXITY

    S(n) = O(1)

    Assuming sorting is done in place, only constant additional memory is 
    necessary to hold a couple of running total variables and to perform
    iteration.

*/

#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
private:
    int findFirstNonNegIndex(std::vector<int>& array) {
        int i{ 0 };
        int j{ static_cast<int>(array.size()) - 1 };
        while (i <= j) {
            int m{ (i + j) / 2 };
            if (array[m] >= 0) {
                if (m == 0 || array[m - 1] < 0)
                    return m;
                else 
                    j = m - 1;
            } else {
                i = m + 1;
            }
        }
        return -1;
    }
public:
    int maxSatisfaction(std::vector<int>& satisfaction) {
        std::sort(satisfaction.begin(), satisfaction.end());

        int firstNonNegInd{ findFirstNonNegIndex(satisfaction) };
        
        if (firstNonNegInd == -1)
            return 0;

        int nonNegSum{ 0 };
        int order{ 1 };
        int nonNegOrderedSum{ 0 };
        for (int i{ firstNonNegInd }; i < satisfaction.size(); ++i) {
            nonNegSum += satisfaction[i];
            nonNegOrderedSum += order * satisfaction[i];
            ++order;
        }
    
        int maxOrderedSum{ nonNegOrderedSum };

        int cumNegSum{ 0 };
        for (int i{ firstNonNegInd - 1 }; i > -1; --i) {
            cumNegSum += satisfaction[i];
            nonNegOrderedSum += cumNegSum + nonNegSum;
            maxOrderedSum = std::max(maxOrderedSum, nonNegOrderedSum);
        }

        return maxOrderedSum;
    }
};

int main() {
    std::vector<int> sats{ -1,-8,0,5,-9 };
    Solution s{};
    int max{ s.maxSatisfaction(sats) };
    std::cout << max << '\n';
}
