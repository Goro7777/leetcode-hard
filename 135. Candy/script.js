/*

SOURCE

    https://leetcode.com/problems/candy/


EXPLANATION

We need to minimize candy count while satisfying 2 requirements:
1. each child must have at least one candy,
2. children with a higher rating get more candies than their neighbors.

First, we iterate from left to right initially assigning each child 1 
candy and comparing their rating to that of the neighbor to the left.
If the rating of the current child is greater, we increment the candy 
count. Thus, we satisfy requirement 1 and the first part of requirement 
2 (in relation to left neighbors). We also achieve the goal of minimizing
the candy count because, for each child, we start with the minimal number, 
1, and increase it by 1 only when that is required to satisfy the first 
part of requirement 2.

Then, we iterate from right to left looking at right neighbors. If the 
current child has a higher rating but a lower candy count, we set the count 
to 1 greater than that of the right neighbor. Thus, we satisfy the second 
part of requirement 2, while still minimizing the candy count.

Note that during the second pass, any time we break the relationship of a 
given child with its left neighbor (based on a comparison with the right 
neighbor), we fix it on the very next iteration, when the left neighbor 
becomes the current child and the previously current child becomes the 
right neighbor. So, after the second pass, both requirements are satisfied.

Finally, we sum the individual candy counts and return the total.


TIME COMPLEXITY

    T(n) = O(n)

    We only make two linear passes to calculate each child's candy count
    and one additional pass to get the total.


SPACE COMPLEXITY

    S(n) = O(n)

    A linear amount of space is needed to store the candy counts. 

*/

function candy(ratings) {
    let candies = new Array(ratings.length);
    
    // consider neighbours to the left
    candies[0] = 1;
    for (let i = 1; i < candies.length; ++i) {
        if (ratings[i] > ratings[i - 1])
            candies[i] = candies[i - 1] + 1;
        else 
            candies[i] = 1;
    }

    // consider neighbours to the right also
    for (let i = ratings.length - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1])
            candies[i] = Math.max(candies[i], candies[i + 1] + 1);
    }

    return candies.reduce((sum, value) => sum + value);   
}

let ratings = [1, 3, 4, 5, 2];
let result = candy(ratings);
console.log(result);
