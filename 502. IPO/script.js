/*

SOURCE

    https://leetcode.com/problems/ipo/
    

ALGORITHM

    We build the sequence of projects that maximizes the final capital by k steps.
    At each step, we 1) select the project with the greatest profit among those 
    that we can currently afford, 2) complete that project by adding its profit 
    to the current capital, 3) add the new projects that are now affordable (with 
    the increased capital) to the pool of projects we are selecting from.
    At the end of (at most) k steps we return our current capital as the final capital.


PROOF OF CORRECTNESS

    We prove that the sequence of projects built by the greedy strategy of 
    selecting the most profitable, affordable project at each step maximizes our
    final capital by comparing it with some arbitrary optimal sequence (there may
    be many).

    At each step of building our sequence, consider the following three mutually 
    exclusive and exhaustive scenarios:
    1) If the optimal sequence includes the most profitable, currently available 
    project (p1) at that step, then we are done - we can add that project to the 
    sequence that we are building and move on to the next step. 
    2) If the optimal sequence does not include p1 at the current step, but includes 
    it at some other future step, we can swap p1 with whatever project is selected at
    the current step (p2) selecting p1 instead (and p2, possibly, at a future step).
    Final capital will not suffer from this because the order of selection does not 
    impact it if the same projects are still selected. Also, p2 or any other subsequent 
    project in the optimal sequence will still be affordable because completing p1 
    earlier will provide us with more capital for future projects.
    3) Finally, if the optimal sequence does not include p1 at the current step and 
    also does not include it ay any future step, we can actually improve it by selecting 
    p1. Since p1 provides more profit than whatever project is selected in its place in 
    the optimal sequence, this will only increase the current, and final capital. 

    Thus, selecting the most profitable, affordable project at each step will always be
    consistent with an optimal sequence of projects maximizing the final capital.


TIME COMPLEXITY

    T(n) = O(n logn)

    We sort the projects by capital to be able to easily add the next group of affordable 
    projects at each step. This takes O(n logn) time.

    The pool of affordable project is organized into a max heap, where insertion and
    extraction operations take O(logn) time. Since, in the worst case, all projects 
    will be available at once, this is also O(n logn).

    Thus, T(n) = O(n logn) + O(n logn) = O(n logn)


SPACE COMPLEXITY

    S(n) = O(n)

    We assume that the sorting is done in place, so it does not add memory requirements.
    However, linear space is required to maintain the heap of locally available projects.

*/

class MaxHeap {
    constructor(lessThan) {
        this.values = [];
        this.lessThan = lessThan;
        // this.buildHeap();
    }

    siftUp(ind) {
        while (true) {
            let parInd = Math.floor((ind - 1) / 2);
            if (parInd < 0 || this.lessThan(this.values[ind], this.values[parInd]))
                return;

            [this.values[parInd], this.values[ind]] = [this.values[ind], this.values[parInd]];
            ind = parInd;
        }
    }

    siftDown(ind) {
        while (true) {
            let swapChildInd = ind;

            let leftChildInd = ind * 2 + 1;
            if (leftChildInd < this.values.length && this.lessThan(this.values[ind], this.values[leftChildInd]))
                swapChildInd = leftChildInd;

            let rightChildInd = leftChildInd + 1;
            if (rightChildInd < this.values.length && this.lessThan(this.values[swapChildInd], this.values[rightChildInd]))
                swapChildInd = rightChildInd;

            if (ind == swapChildInd)
                break;

            [this.values[ind], this.values[swapChildInd]] = [this.values[swapChildInd], this.values[ind]];
            ind = swapChildInd;
        }
    }

    isEmpty() {
        return this.values.length == 0;
    }

    extractMax() {
        let lastInd = this.values.length - 1;
        [this.values[0], this.values[lastInd]] = [this.values[lastInd], this.values[0]];
        let maxValue = this.values.pop();
        this.siftDown(0);
        return maxValue;   
    }

    insert(value) {
        this.values.push(value);
        this.siftUp(this.values.length - 1);   
    }
}

function findMaximizedCapital(k, w, profits, capital) {
    let projects = new Array(capital.length);
    for (let i = 0; i < capital.length; ++i)
        projects[i] = [capital[i], profits[i]];

    projects.sort((proj1, proj2) => (proj1[0] < proj2[0]) ? -1 : 1);

    let availableProjects = new MaxHeap((proj1, proj2) => proj1[1] < proj2[1]);
    let i = 0;
    let projectsCompleted = 0;

    while (projectsCompleted < k) {
        while (i < projects.length && projects[i][0] <= w)
            availableProjects.insert(projects[i++]);

        if (availableProjects.isEmpty())
            break;

        let maxProfitAvailableProject = availableProjects.extractMax();
        w += maxProfitAvailableProject[1];
        ++projectsCompleted;
    }

    return w;
};

let k = 2, w = 0, profits = [1,2,3], capital = [0,1,1];
// let k = 3, w = 0, profits = [1,2,3,1,5,6,2,10,0,1], capital = [0,1,2,3,4,5,6,7,8,9];
let res = findMaximizedCapital(k, w, profits, capital);
console.log(res);

// let vals = [1,2,3,1,5,6,2,10,0,1];
// let heap = new MaxHeap((a, b) => a < b);
// for (let v of vals) {
//     heap.insert(v);
// }
// while (!heap.isEmpty())
//     console.log(heap.extractMax());

