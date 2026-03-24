# CSF303 Algorithm Design
# Programming Assignment Report
## Problems 1 through 6

---

## Problem 1: Dinner Table Arrangements

### a. Problem Summary
Given N friends each with a set of food allergies represented as bitmasks, determine whether they can be seated around a circular table such that no two adjacent friends share any common allergy. The task requires finding a valid circular arrangement across multiple test cases.

### b. Algorithm Explanation
- The core idea is to find a Hamiltonian Cycle in a compatibility graph where each friend is a node and an edge exists between two friends if and only if their allergy bitmasks have no overlapping bits (bitwise AND equals zero).
- **Step 1 - Build bitmasks**: For each friend, read their allergy IDs and set the corresponding bit. Friend with allergies {1, 2} gets mask = (1<<1) | (1<<2) = 6.
- **Step 2 - Bitmask DP**: Define dp[seated][last] = true if we can seat exactly the friends represented by the bitmask 'seated', with friend 'last' at the open end of the chain. Friend 0 is fixed as the starting position to eliminate counting circular rotations as different arrangements.
- **Step 3 - Transitions**: For each valid state dp[seated][last], try adding each unseated friend 'next' if compatible(last, next) is true, i.e., mask[last] & mask[next] == 0.
- **Step 4 - Close the circle**: After all N friends are placed (seated == FULL), check if any last-placed friend is also compatible with friend 0 to complete the circular arrangement.

### c. Time Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| Time | O(2^N × N²) | 2^N states, N choices of last friend, N transitions each. |
| Space | O(2^N × N) | DP table of size 2^N × N booleans. |

### d. Space Complexity Analysis
As shown in the complexity table above: DP table of size 2^N × N booleans.

### e. Reflection
This problem deepened my understanding of Hamiltonian Cycle problems and how bitmask DP elegantly encodes subset states. Initially, I considered checking all N! permutations, but that is infeasible for N=20. Fixing friend 0 as the anchor to eliminate rotational duplicates was a key insight that reduced the search space. The bitwise AND check for compatibility made the allergy comparison both fast and clean.

---

## Problem 2: Maximum AND Subarray

### a. Problem Summary
Given an array of N integers, find the maximum AND value achievable over any contiguous subarray of exactly length K. The AND operation over a subarray tends to produce smaller values as the subarray grows, so the problem asks for the optimal fixed-size window.

### b. Algorithm Explanation
- The approach is a greedy bit-by-bit construction from the most significant bit (MSB) down to the least significant bit (LSB).
- **Step 1 - Start with answer = 0**: For each bit b from bit 29 down to bit 0, tentatively set that bit in the answer: candidate = answer | (1 << b).
- **Step 2 - Check feasibility**: Scan the array and count consecutive elements where (A[i] & candidate) == candidate. If any run of length >= K exists, then all elements in that run have all the bits in candidate set, so their AND will also have all those bits set.
- **Step 3 - If feasible, keep the bit**: answer = candidate. Otherwise, discard it. This greedy works because setting higher bits always contributes more value than any combination of lower bits.

### c. Time Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| Time | O(30 × N) | 30 bits checked, each requiring a single linear scan of the array. |
| Space | O(N) | Only the input array and a constant number of variables are used. |

### d. Space Complexity Analysis
As shown in the complexity table above: Only the input array and a constant number of variables are used.

### e. Reflection
This problem taught me how to apply a greedy bitwise strategy. I initially tried checking all subarrays of length K and computing their AND, which is O(NK) and times out for large inputs. The key insight is that bits are independent in terms of their contribution to the AND result, so we can decide greedily from the most significant bit. The feasibility check collapses to a simple consecutive-run scan, making the solution very efficient.

---

## Problem 3: Sliding Window Maximum

### a. Problem Summary
Given an array of N integers and a window size K, output the maximum element in each contiguous subwindow of size K as the window slides from left to right. There are N-K+1 such windows in total.

### b. Algorithm Explanation
- The efficient solution uses a monotonic deque (double-ended queue) that stores indices of array elements in decreasing order of their values.
- **Step 1 - For each new element at index i**: first remove from the front of the deque any index that has fallen outside the current window (index <= i - K).
- **Step 2 - Remove from the back**: of the deque any index j where A[j] <= A[i], because A[j] can never be the maximum for any future window that includes A[i].
- **Step 3 - Push index i**: to the back of the deque.
- **Step 4 - Output maximum**: Once i >= K-1, the front of the deque holds the index of the maximum element in the current window. Output A[deque.front()].
- The deque maintains the invariant that elements are always in decreasing order, so the front is always the maximum.

### c. Time Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| Time | O(N) | Each element is pushed and popped from the deque at most once. |
| Space | O(K) | The deque holds at most K indices at any time. |

### d. Space Complexity Analysis
As shown in the complexity table above: The deque holds at most K indices at any time.

### e. Reflection
This problem was my first encounter with the monotonic deque technique. A brute force O(NK) solution works for small inputs but fails at scale. The key insight is that if element A[j] is smaller than A[i] and j < i, then A[j] will never be the window maximum for any window that contains A[i]. Discarding it eagerly from the deque is safe and gives us the O(N) solution. The deque essentially maintains a decreasing sequence of useful candidates.

---

## Problem 4: Maximum in Sliding Window with Updates

### a. Problem Summary
An extension of Problem 3 that supports point update queries in addition to sliding window maximum queries. Given an array and two query types (update a value, query the maximum in a window of size K ending at index i), process all queries efficiently.

### b. Algorithm Explanation
- A pure deque approach breaks down with point updates since updates can affect previously discarded elements. Instead, a Segment Tree is used for O(log N) range-max queries and O(log N) point updates.
- **Step 1 - Build**: Construct a segment tree over the array where each node stores the maximum of its range. Build time is O(N).
- **Step 2 - Update (Type 1)**: Given position pos and value val, update the leaf at pos and propagate the change upward through the tree, updating the max at each internal node. Cost: O(log N).
- **Step 3 - Query (Type 2)**: For a query at index i with window size K, perform a range-max query on the interval [i-K+1, i]. The segment tree answers this in O(log N) by combining results from overlapping tree nodes.

### c. Time Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| Time | O((N + Q) log N) | Build is O(N); each of the Q queries costs O(log N). |
| Space | O(N) | Segment tree uses 4*N nodes in the backing array. |

### d. Space Complexity Analysis
As shown in the complexity table above: Segment tree uses 4*N nodes in the backing array.

### e. Reflection
This problem taught me when to upgrade from a specialized data structure (deque) to a more general one (segment tree). The monotonic deque is faster for static arrays but cannot efficiently handle updates. Building the segment tree made me appreciate how a binary tree structure enables both updates and range queries in logarithmic time. The pattern of 'build once, query and update many times' is a foundational competitive programming paradigm.

---

## Problem 5a: Network Latency (Shortest Path)

### a. Problem Summary
Given a network of N routers connected by M bidirectional cables each with a given latency, find the minimum total latency to send a packet from router 1 to router N. Output -1 if no path exists between them.

### b. Algorithm Explanation
- This is a classic single-source shortest path problem on a weighted undirected graph, solved with Dijkstra's algorithm using a min-heap.
- **Step 1 - Build adjacency list**: For each cable (u, v, w), add both directions to the adjacency list.
- **Step 2 - Initialize distances**: Set dist[1] = 0 and dist[i] = infinity for all other nodes. Push (0, 1) into the min priority queue.
- **Step 3 - Relaxation**: Pop the node u with minimum current distance. For each neighbor v with edge weight w, if dist[u] + w < dist[v], update dist[v] and push (dist[v], v) to the queue.
- **Step 4 - Lazy deletion**: If the popped distance is greater than the stored dist[u], skip it (stale entry).
- **Step 5 - Output** dist[N], or -1 if it remains infinity.

### c. Time Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| Time | O((N + M) log N) | Each edge is relaxed once; priority queue operations cost O(log N). |
| Space | O(N + M) | Adjacency list stores M edges; distance array stores N values. |

### d. Space Complexity Analysis
As shown in the complexity table above: Adjacency list stores M edges; distance array stores N values.

### e. Reflection
Implementing Dijkstra reinforced my understanding of greedy shortest-path algorithms. The use of a priority queue to always process the closest unvisited node ensures optimality. I learned that the 'lazy deletion' trick (checking if d > dist[u] before processing) is simpler than maintaining a decrease-key structure and works efficiently for competitive programming. Handling the -1 case by checking if dist[N] remains at LLONG_MAX is an important edge case.

---

## Problem 5b: Time-Dependent Shortest Path

### a. Problem Summary
Given N intersections and M directed roads where each road has a travel time function f(t) = a*t + b (the travel time depends on departure time t), find the earliest arrival time at intersection N when starting from intersection 1 at time 0.

### b. Algorithm Explanation
- This is a modified Dijkstra problem. The key property that makes Dijkstra applicable is that the edge functions are FIFO (First In, First Out): departing later never results in earlier arrival, since a*t + b is non-decreasing for a >= 0.
- **Step 1 - Model edges**: For a directed edge u -> v with function f(t) = a*t + b, if you depart from u at time t, you arrive at v at time t + f(t) = t*(1+a) + b.
- **Step 2 - Modified Dijkstra**: Use a min-heap on arrival times. dist[i] represents the earliest time you can be at node i.
- **Step 3 - Relaxation**: When processing node u with current time d, for each outgoing edge (u, v, a, b), compute arrival = d*(1+a) + b. If arrival < dist[v], update and push to queue.
- **Step 4 - Output** dist[N] rounded to 2 decimal places, or -1 if unreachable.

### c. Time Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| Time | O((N + M) log N) | Same as standard Dijkstra; FIFO property ensures correctness. |
| Space | O(N + M) | Adjacency list and distance array only. |

### d. Space Complexity Analysis
As shown in the complexity table above: Adjacency list and distance array only.

### e. Reflection
This variant taught me how to verify whether Dijkstra is applicable to non-standard edge weights. The critical insight is the FIFO property: since a >= 0, the function f(t) = a*t + b is non-decreasing, meaning departing later never helps. Without this, Dijkstra could produce incorrect results. Floating-point precision was also a challenge; using double and comparing with a small epsilon (1e-9) for the stale-entry check ensured correctness.

---

## Problem 6: Shortest Path with Toll Booths

### a. Problem Summary
A highway has N toll booths in a line. Starting at booth 1 with M coins, at each booth you can either pay the toll and advance in 1 minute, or skip the booth in 2 minutes (with at most K total skips allowed). Find the minimum time to reach booth N.

### b. Algorithm Explanation
- This is a dynamic programming problem on a 1D grid with an additional skip-budget dimension.
- **Step 1 - State definition**: dp[i][j] = maximum coins remaining when standing at booth i having used exactly j skips. We maximize coins (instead of minimizing time) because having more coins enables more future pay options.
- **Step 2 - Initialization**: dp[0][0] = M (at booth 1 with M coins, 0 skips used). All other states are -infinity.
- **Step 3 - Transitions from booth i with j skips used**:
  - **Option A (Pay)**: If dp[i][j] >= toll[i+1], move to booth i+1 paying toll: dp[i+1][j] = max(dp[i+1][j], dp[i][j] - toll[i+1]). Costs 1 minute.
  - **Option B (Skip)**: If j < K, move to booth i+1 skipping: dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]). Costs 2 minutes.
- **Step 4 - Answer**: Scan dp[N-1][j] for j = 0 to K. The first j with a valid (non -infinity) state gives the minimum time = (N-1) + j, since j skips add j extra minutes.

### c. Time Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| Time | O(N × K) | N booths, K+1 skip states per booth, O(1) transitions each. |
| Space | O(N × K) | DP table of size N × (K+1). |

### d. Space Complexity Analysis
As shown in the complexity table above: DP table of size N × (K+1).

### e. Reflection
This problem taught me how to model optimization problems with multiple constraints using 2D DP. The key insight is framing the state as maximizing remaining coins rather than directly minimizing time, which simplifies transition logic. I also learned to scan the final row in order of skip count (j = 0, 1, ..., K) so the first valid answer corresponds to the minimum extra time incurred. Handling the -1 case (no path exists even with all skips) required checking whether all states at booth N remain at -infinity.

---

## Summary

This programming assignment covered six diverse algorithmic problems spanning multiple domains:

1. **Graph Theory & Combinatorics** (Problem 1): Hamiltonian Cycles via bitmask DP
2. **Bitwise Operations & Greedy** (Problem 2): Bit-by-bit greedy construction
3. **Deque Data Structure** (Problem 3): Monotonic deque for sliding window
4. **Advanced Data Structures** (Problem 4): Segment tree for dynamic range queries
5. **Shortest Path Algorithms** (Problems 5a & 5b): Dijkstra on standard and time-dependent graphs
6. **Dynamic Programming** (Problem 6): DP with auxiliary constraints

Each problem reinforced fundamental competitive programming techniques and taught valuable lessons about algorithm selection, data structure choice, and optimization strategies.
