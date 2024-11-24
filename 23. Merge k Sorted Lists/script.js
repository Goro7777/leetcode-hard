/*

SOURCE

    https://leetcode.com/problems/merge-k-sorted-lists/

    
EXPLANATION

    We build the merged linked-list node by node. Since the input linked-lists
    are arranged in ascending order, each time when selecting a node for the merged
    list, it has to be the node with the minimum value among the nodes that are 
    at that moment at the fronts of the input linked-lists. If any other node is 
    selected, the front node of the list the node was selected from will have 
    to follow the selected node in the merged list disturbing the sort order. 


TIME COMPLEXITY

    T(n, k) = O(n logk),
    where n is total the number of nodes and k is the number of linked-lists.

    We put the nodes from the front of the input lists into a min-heap. Each time
    we extract the minimum node from the heap, we add the node following it in 
    the input linked-list to the heap. Since there are k input lists, and at any 
    given moment (at most) one node is present in the heap from each list, the 
    size of the heap is k, and the extraction and insertion operations will take
    O(logk) time for each node. Since all n nodes pass through the heap, 
    T(n, k) = O(n logk).


SPACE COMPLEXITY

    S(n, k) = O(k)

    Since the maximum size of the heap is k, we only need O(k) amount of
    additional space.

*/

class MinHeap {
    constructor() {
        this.values = [];
    }

    getSize() { return this.values.length; }

    siftUp(ind) {
        while (true) {
            let parInd = Math.floor((ind - 1) / 2);
            if (parInd < 0 || this.values[parInd].val < this.values[ind].val)
                return;

            [this.values[parInd], this.values[ind]] = [this.values[ind], this.values[parInd]];
            ind = parInd;
        }
    }

    siftDown(ind) {
        while (true) {
            let swapChildInd = ind;

            let leftChildInd = ind * 2 + 1;
            if (leftChildInd < this.values.length && this.values[leftChildInd].val < this.values[ind].val)
                swapChildInd = leftChildInd;

            let rightChildInd = leftChildInd + 1;
            if (rightChildInd < this.values.length && this.values[rightChildInd].val < this.values[swapChildInd].val)
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

    extractMin() {
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

var mergeKLists = function(lists) {
    let head = null;
    let tail = null;
    let heap = new MinHeap();


    for (let node of lists) {
        if (node)
            heap.insert(node);
    }
    while (heap.getSize() > 0) {
        let node = heap.extractMin();
        if (node.next)
            heap.insert(node.next);
        node.next = null;
        if (!head) {
            head = tail = node;
        } else {
            tail.next = node;
            tail = node;
        }
    }

    return head;
};