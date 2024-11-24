/*

SOURCE

    https://leetcode.com/problems/ipo/


ALGORITHM

    We build the sequence of projects that maximizes the final capital by k steps.
    At each step, we 1) select the project with the greatest profit among those 
    that we can currently afford, 2) complete that project by adding its profit 
    to the current capital, 3) add new projects that are now affordable (with 
    the increased capital) to the pool of projects we are selecting from. At the
    end of (at most) k steps we return our current capital as the final capital.


PROOF OF CORRECTNESS

    We prove that the sequence of projects built by the greedy strategy of 
    selecting the most profitable, affordable project at each step maximizes our
    final capital by comparing this sequence with some arbitrary optimal sequence 
    (there may be many).

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

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

template <typename T>
class MaxHeap {
private:
    std::vector<T> m_values;
    bool (*m_lessThan)(const T& el1, const T& el2){ nullptr };

public:
    MaxHeap(bool (*lessThan)(const T& el1, const T& el2))
        : m_values{ std::vector<T>() }, m_lessThan{ lessThan } {}
    
    void siftUp(int ind) {
        while (true) {
            int parInd{ static_cast<int>( std::floor((ind - 1) / 2.0) ) };
            if (parInd < 0 || m_lessThan(m_values[ind], m_values[parInd]))
                return;

            std::swap(m_values[parInd], m_values[ind]);
            ind = parInd;
        }
    }

    void siftDown(int ind) {
        while (true) {
            int swapChildInd{ ind };

            int leftChildInd{ ind * 2 + 1 };
            if (leftChildInd < m_values.size() && m_lessThan(m_values[ind], m_values[leftChildInd]))
                swapChildInd = leftChildInd;

            int rightChildInd{ leftChildInd + 1 };
            if (rightChildInd < m_values.size() && m_lessThan(m_values[swapChildInd], m_values[rightChildInd]))
                swapChildInd = rightChildInd;

            if (ind == swapChildInd)
                break;

            std::swap(m_values[ind], m_values[swapChildInd]);
            ind = swapChildInd;
        }
    }

    bool isEmpty() {
        return m_values.size() == 0;
    }

    T extractMax() {
        int lastInd{ static_cast<int>( m_values.size() ) - 1 };
        std::swap(m_values[0], m_values[lastInd]);
        T maxValue{ m_values[lastInd] }; 
        m_values.pop_back();
        siftDown(0);
        return maxValue;   
    }

    void insert(const T& value) {
        m_values.push_back(value);
        siftUp(static_cast<int>( m_values.size() ) - 1);   
    }
};

class Solution {
public:
    int findMaximizedCapital(int k, int w, std::vector<int>& profits, std::vector<int>& capital) {
        std::vector<std::vector<int>> projects( capital.size() );
        for (int i{ 0 }; i < capital.size(); ++i)
            projects[i] = { capital[i], profits[i] };

        std::sort( projects.begin(), projects.end(), [](const auto& p1, const auto& p2) {
            return p1[0] < p2[0];
        } );

        MaxHeap<std::vector<int>> availableProjects{ [](const auto& proj1, const auto& proj2) 
            { return proj1[1] < proj2[1]; } };
        int i{ 0 };
        int projectsCompleted{ 0 };

        while (projectsCompleted < k) {
            while (i < projects.size() && projects[i][0] <= w)
                availableProjects.insert(projects[i++]);

            if (availableProjects.isEmpty())
                break;

            auto maxProfitAvailableProject{ availableProjects.extractMax() };
            w += maxProfitAvailableProject[1];
            ++projectsCompleted;
        }

        return w;   
    }
};


bool lessThan(const int& a, const int& b) {
    return a < b;
}

int main() {
    int k{ 2 };
    int w{ 0 };
    std::vector profits{ 1, 2, 3};
    std::vector capital{ 0, 1, 1}; 

    Solution s{};
    int count{ s.findMaximizedCapital(k, w, profits, capital) };
    std::cout << count << '\n';
}