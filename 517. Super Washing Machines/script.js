/*

SOURCE

    https://leetcode.com/problems/super-washing-machines/


TIME COMPLEXITY

    T(n) = O(n)

    We make two passes through the input array, once to calculate the
    total number of dresses and once to calculate the number of moves
    each of the machines is involved in.


SPACE COMPLEXITY

    S(n) = O(1)

*/

function findMinMoves(machines) {
    let machinesTotal = machines.length;
    let dressesTotal = machines.reduce((acc, dress) => acc + dress);

    if (dressesTotal % machinesTotal != 0)
        return -1;

    let targetDresses = dressesTotal / machinesTotal;
    
    let cumulDresses = machines[0];
    let passLeft = 0;
    let passRight = (machines[0] > targetDresses) ? (machines[0] - targetDresses) : 0;
    let getFromLeft = 0;
    let getFromRight = (machines[0] < targetDresses) ? (targetDresses - machines[0]) : 0;
    
    let moves = Math.max(passRight, getFromLeft, getFromRight);

    for (let i = 1; i < machinesTotal; ++i) {
        passLeft = getFromRight;
        getFromLeft = passRight;

        cumulDresses += machines[i];
        let targetCumulDresses = (i + 1) * targetDresses;
        if (cumulDresses > targetCumulDresses) {
            passRight = cumulDresses - targetCumulDresses;
            getFromRight = 0;
        } else if (cumulDresses < targetCumulDresses) {
            passRight = 0;
            getFromRight = targetCumulDresses - cumulDresses;
        } else {
            passRight = 0;
            getFromRight = 0;
        }

        moves = Math.max(moves, passLeft + passRight, getFromLeft, getFromRight);
    }

    return moves;
};

let machines = [0,3,0];
let res = findMinMoves(machines);
console.log(res);