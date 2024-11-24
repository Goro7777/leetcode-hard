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

#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>

template <typename T>
class MinHeap {
protected:
    std::vector<T> m_values{};
        
    void siftUp(int i);  
    void siftDown(int i);  

    int getParentInd(int i) { return (i - 1) / 2; }
    int getLeftChildInd(int i) { return i * 2 + 1; }
    int getRightChildInd(int i) { return i * 2 + 2; }

public:
    void insert(const T& value);
    T extractMin();
    std::size_t getSize() const { return m_values.size(); }
};

template <typename T>
void MinHeap<T>::siftUp(int ind) {
    while (ind > 0) {
        int parInd{ getParentInd(ind) };
        if (m_values[ind]->val < m_values[parInd]->val) {
            std::swap( m_values[ind], m_values[parInd]);
            ind = parInd;
        } else {
            break;
        }
    }
}

template <typename T>
void MinHeap<T>::siftDown(int ind) {
    while (true) {
        int childSwapInd{ ind };
        
        int leftChildInd{ getLeftChildInd(ind) };
        if (leftChildInd < m_values.size() && m_values[leftChildInd]->val < m_values[ind]->val)
            childSwapInd = leftChildInd;

        int rightChildInd{ getRightChildInd(ind) };
        if (rightChildInd < m_values.size() && m_values[rightChildInd]->val < m_values[childSwapInd]->val)
            childSwapInd = rightChildInd;

        if (childSwapInd == ind)
            break;

        std::swap( m_values[ind], m_values[childSwapInd] );
        ind = childSwapInd;
    }
}

template <typename T>
void MinHeap<T>::insert(const T& value) {
    m_values.push_back(value);
    siftUp( m_values.size() - 1 );
}

template <typename T>
T MinHeap<T>::extractMin() {
    T minValue{ m_values[0] };
    std::swap( m_values[0], m_values[m_values.size() - 1] );
    m_values.pop_back();
    siftDown(0);
    return minValue;
}


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        ListNode* head{ nullptr };
        ListNode* tail{ nullptr };

        MinHeap<ListNode*> heap{};

        for (ListNode* node : lists) {
            if (node)
                heap.insert(node);
        }

        while (heap.getSize() > 0) {
            ListNode* node = heap.extractMin();
            if (node->next)
                heap.insert(node->next);
            node->next = nullptr;
            if (!head) {
                head = tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }

        return head;
    }
};

int main() {
    // std::vector<int> values{ 1, 10, 5, 4, 9, 0, 1, 4, 6, 4, 8, 7, 0, 5 };
    // MinHeap<int> h{};

    // for (int el : values) 
    //     h.insert(el);
    
    // while (h.getSize() > 0)
    //     std::cout << h.extractMin() << '\n';
    
}