# ALGORITHMS & DATA STRUCTURES
## Lab Assignment Report

---

# ASSIGNMENT 1 (15 Marks)
## Topics: STL · Bellman-Ford · Floyd-Warshall

---

## Question 1: STL Containers in C++

The assignment wanted me to actually use STL properly—not just declare containers and loop through them like arrays. Three separate challenges: reverse a vector cleanly using iterators, track a deque's state through multiple push and pop operations, and sum an array using STL functions instead of a manual loop.

### What I Actually Did

Part (a) was straightforward. I threw N integers into a vector, then used `rbegin()` and `rend()` to iterate backwards. Could've used a reverse index loop—would've been faster to write—but the whole point was showing I know STL idioms. When I ran it with {10, 20, 30, 40, 50}, it spit out 50 40 30 20 10. Exactly right. O(N) time, O(N) space for storing the vector.

Part (b) actually made me think. A deque supports O(1) insertions at both ends, which is literally why you'd use it instead of a vector. I ran seven operations in sequence: push_back(10), push_back(20), push_front(5), push_front(1), pop_front(), push_back(30), pop_front(). Watching the deque at each step was illuminating. The 1 got removed first, then the 5—confirming FIFO from the front. Final state: [10, 20, 30]. Each operation is O(1). The tracking itself is O(N) space.

Part (c) was the one that almost tripped me. std::accumulate lives in `<numeric>`, not `<algorithm>`. I declared `array<int,6> = {3, 7, 1, 9, 4, 6}` and called `accumulate(arr.begin(), arr.end(), 0)`. Returned 30. What's interesting about array is that the size is baked in at compile time—no dynamic allocation overhead. O(N) time to sum, O(1) space since size is fixed.

### Key Complexity Numbers

| Operation | Time | Space |
|-----------|------|-------|
| Vector reverse iteration | O(N) | O(N) storage |
| Deque operations (each) | O(1) | O(N) total |
| Array sum via accumulate | O(N) | O(1) fixed |

### What I Learned

The reverse iterator syntax felt weird at first. I kept wanting to just write a for loop counting down. But once I saw how cleanly `rbegin()/rend()` reads in actual code, it made sense. It's more intention-revealing—you're not manually managing indices, you're just saying "iterate backwards." Another thing: understanding that deque maintains O(1) at both ends but vector doesn't changed how I think about container selection. Use vector when you mostly access and modify the end. Use deque when you're beating on both sides. Use array when the size never changes. Right tool, right job.

### Output Screenshot

![alt text](Assignment_1/Q1.png)

---

## Question 2: Bellman-Ford Algorithm

### Problem Summary
Given a directed graph with V vertices, E edges (weights may be negative):
- Compute shortest paths from a source vertex to all other vertices
- Detect the presence of negative weight cycles
- Output the final shortest distance table

**Constraint**: V ≤ 1000, E ≤ 10000 (implied by typical problem bounds)

### Algorithm Explanation

**Core Concept**: Relaxation-based shortest path algorithm

The Bellman-Ford algorithm works by iteratively relaxing edges:
- **Relaxation**: If `dist[u] + weight(u,v) < dist[v]`, update `dist[v]`
- **Key Principle**: After k passes, all shortest paths using ≤ k edges are found
- **Why V-1 passes?**: Any shortest path without cycles uses at most V-1 edges

**Negative Cycle Detection**:
- If a Vth pass still relaxes any edge → negative cycle exists
- Indicates distances are still decreasing → would decrease forever if continued

### How I Coded It

I stored all edges in a `vector<Edge>` where each edge has u, v, w (from, to, weight). This flat structure makes iteration clean. Initialization was straightforward: `dist[src] = 0`, everything else = INT_MAX. Then the main loop: V-1 times, scan every edge. For each edge, check if relaxation is possible.

The guard is everything: `if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v])`. Skip that check and INT_MAX + anything overflows to a negative number. Spent 20 minutes debugging that. After V-1 passes, I scan edges one final time—if anything relaxes, negative cycle exists.\n
The input was 1-indexed but distances array was 0-indexed. Converting vertex 1 to index 0 fixed a bug where vertex 1 showed INF instead of 0. Easy to miss.

**Complexity Breakdown**

O(V × E) time: V-1 relaxation passes scanning all E edges, plus O(E) cycle check. Space is O(V + E)—distance array plus edge list. Dijkstra hits O((V + E) log V) but demands non-negative weights. Bellman-Ford trades speed for generality.\n
**What Stuck With Me**

The algorithm is conceptually boring—relax edges repeatedly. But that simplicity is powerful. Cycle detection comes nearly free. The overflow bug? Painful at the time but unforgettable. INT_MAX is dangerous. Use 1e9 instead. Dense graphs destroy this algorithm (E near V² makes it O(V³)), so Dijkstra wins there. For sparse graphs, Bellman-Ford doesn't apologize.

### Output Screenshot (No Negative Cycle)

![alt text](Assignment_1/Q2.png)

### Output Screenshot (Negative Cycle Detected)

![alt text](Assignment_1/Q2_negative.png)

---

## Question 3: Floyd-Warshall Algorithm

All-pairs shortest paths: compute every distance between every vertex pair. Needs to work with negative weights, detect negative cycles, print the distance matrix. Sounds simple enough.

### The Actual Algorithm

Three nested loops. That's it. For each intermediate vertex k, check if routing through it beats the current best. The recurrence is `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`. Simple.

What makes this work with negative weights? No greedy assumptions. Dijkstra assumes everything's non-negative so it can bail early. Floyd-Warshall doesn't care. A weight of -4? Just means routing that way saves 4 units. DP handles it naturally.

Negative cycles break everything. Let me think through this. If I have a cycle with total weight -10, I can keep looping and make my path cost drop forever. The algorithm detects it by checking if the diagonal goes negative: if `dist[i][i] < 0`, then vertex i is part of a cycle. That check caught the bug.

### Implementation Reality

Initialization: `dist[i][i] = 0`, actual edge weights go in their spots, everything else is INF. Here's the trap: **use 1e9 as INF, not INT_MAX**. INT_MAX + INT_MAX overflows. Spent an hour on that bug. With 1e9, adding two values gives 2e9 which is safely under INT_MAX.

The three nested loops run V times each: k, i, j. Before adding, I check `if dist[i][k] < INF and dist[k][j] < INF`. Otherwise overflow hits again.

After all loops finish, scan the diagonal. Any negative value means a cycle. The matrix output needed `setw()` for alignment—took more debugging than the actual algorithm.

### Numbers That Matter

O(V³) time. For V=1000, that's literally 1 billion operations. O(V²) space for the matrix. Running Dijkstra V times with a heap hits O(V × (V+E) log V). For dense graphs, Floyd-Warshall wins. For sparse? Dijkstra from each source destroys it.

When V < 500, O(V³) is fine. Beyond that, density matters.

### What I Realized

The algorithm is almost boring in its simplicity. Three loops, one comparison. But that boring simplicity is powerful. You get an answer with zero doubt about correctness. The negative cycle detection costs almost nothing—just a diagonal scan.

Presentation actually matters. An unaligned matrix is impossible to verify by hand. Learned that the hard way. The math is clean but the implementation required more careful formatting than I expected.

### Output Screenshot

![alt text](Assignment_1/Q3.png)

---

# ASSIGNMENT 2 (15 Marks)
## Topics: Bitmasking · Johnson's · Arbitrage · Edmonds' · KMP & Rabin-Karp

---

## Question 1: Bitmasking - Subset Generation & Divisibility Count

Given N integers (N ≤ 20) and divisor K, generate all subsets and count how many have sums divisible by K. The constraint N ≤ 20 is the whole story—that's 2^20 ≈ 1 million subsets. Doable. 2^25 would kill the runtime.

### How Bitmasking Works

Each integer from 0 to (2^N - 1) encodes one subset. Bit i being set means arr[i] is included. Mask=5 in binary is 101, so take arr[0] and arr[2]. Mask=0 is the empty set. Mask=15 with N=4 gives all four elements. It's a one-to-one mapping.

No recursion needed, so no stack overhead. The ordering is deterministic. You iterate and pick subsets in increasing mask order. Makes debugging easy because the output is reproducible.

### What I Actually Coded

Outer loop: mask goes 0 to (2^N - 1). Inner loop: check bits 0 to N-1. For bit i, test `(mask & (1 << i))`. If true, add arr[i] to the current subset and add its value to sum. Then check `sum % K == 0` and increment the counter if true.

Testing with N=4, arr={1,2,3,4}, K=3: got 16 total subsets (correct: 2^4). Counted 6 with sum divisible by 3. Verified by hand: {}, {3}, {1,2}, {1,2,3}, {2,4}, {2,3,4}. All check out.

### Why N ≤ 20 Is The Line

2^20 = 1,048,576 subsets. 20 bit checks per subset. Roughly 20 million operations. CPU crushes that. 2^25 hits 30+ million operations. At that point? Nope. Too slow. That's when you switch to DP: track `dp[i][r]` = "how many subsets of first i elements have sum % K = r". That's O(N × K) which beats 2^N for large N.

The constraint exists exactly to make bitmask the intended solution. Clever constraint design.

### The Learning

Bit manipulation is genuinely elegant. Each integer is a compact encoding of set membership. Operations like `1 << i` and `mask & (1 << i)` are single CPU instructions. The algorithm is O(2^N × N) which sounds exponential—it is—but for N ≤ 20 it's manageable.

Understanding binary representation has downstream value. It shows up in dynamic programming optimization, graph algorithms as bitmasks for visited sets, and even in ML for feature selection. This problem teaches that binary is not just for storing numbers; it's a way of thinking about membership and combinations.

### Output Screenshot

![alt text](Assignment_2/A2_Q1.png)

---

## Question 2: Johnson's Algorithm - Why It Crushes Floyd-Warshall on Sparse Graphs

### The Problem It Solves

All-pairs shortest paths when edges have negative weights but no negative cycles. Floyd-Warshall is O(V³). Johnson's is O(V²log V + VE). For sparse graphs? Johnson dominates. Let me show the math.

Take V=1000, E=5000 (sparse). Floyd-Warshall: 1000³ = 1 billion operations. Johnson's: 1000² × log(1000) + 1000 × 5000 ≈ 10 million operations. **100× faster**. That's not theoretical; that's real.

### How Johnson Pulls It Off

Add a dummy source vertex s with zero-cost edges to every vertex. Run Bellman-Ford from s to get potentials h[v] = shortest distance from s to v. These potentials are the trick.

Reweight every edge: new_weight(u,v) = old_weight(u,v) + h[u] - h[v]. This transformation makes all weights non-negative. Run Dijkstra V times, one from each vertex. Final distances get adjusted back.

The reweighting works because the adjustment cancels when you sum along any path. h[u] gets added, then h[v] gets subtracted. On a complete path A→B→C, the h values eliminate and you get the true relative ordering back.

### Why Bellman-Ford Specifically?

Dijkstra dies on negative weights. Johnson uses Bellman-Ford to build the potentials h[v] because Bellman-Ford handles negatives. It also detects if a negative cycle exists—if one does, the whole algorithm aborts because all-pairs shortest paths don't exist.

That detection is free. One extra pass. If anything relaxes, cycle detected. Clean.

### The Trade-off

Floyd-Warshall is always O(V³). Doesn't matter if you have 10 edges or V² edges. Johnson cares about E. When E is tiny compared to V², Johnson wins hard. When E approaches V², the gap closes. At E = V², they're comparable. For dense graphs, Floyd-Warshall's simplicity and cache locality sometimes beat Johnson despite the worse complexity.

The real insight? Don't use the all-pairs algorithm blindly. Look at density. Make the algorithmic choice data-driven.

---

## Question 3: Arbitrage Detection via Currency Exchange

### The Real Problem

Currencies form a graph. Vertices are currencies. An edge from USD to EUR with weight 1.1 means 1 unit of USD becomes 1.1 units of EUR. Want to find arbitrage: a cycle where you start with 1 unit, make exchanges, and end up with more than 1 unit. Cycle with product of rates > 1.

Example: USD → EUR (×1.1) → GBP (×1.2) → USD (×0.95). Product: 1.1 × 1.2 × 0.95 = 1.254. You turned 1 USD into 1.254 USD. That's profit from nothing. Illegal but the math is clean.

### The Trick: Logarithms

Multiplicative problems are hard in graph algorithms. Everything assumes sums. The fix: take negative logarithm of exchange rates.

r₁ × r₂ × ... × rₖ > 1 becomes log(r₁) + log(r₂) + ... + log(rₖ) > 0 becomes -log(r₁) - log(r₂) - ... - log(rₖ) < 0.

Bam. Multiplicative problem is now additive.

Edge weights are w(u,v) = -log(rate(u,v)). A cycle with product > 1 is now a cycle with sum < 0 (negative cycle).

### Implementation

Read currency pairs and rates. Compute w(u,v) = -log(rate(u,v)). Run Bellman-Ford from any vertex. If a Vth pass relaxes any edge, arbitrage exists. That edge is part of the profitable cycle.

Why Bellman-Ford? The reweighted graph has negative edges (log of rates < 1 gives negative logs, and we negated them). Dijkstra chokes. Floyd-Warshall works but O(V³) for a currency graph is overkill. Bellman-Ford is O(VE), detects cycles, and handles the negative weights naturally.

### What Stands Out

This problem teaches something deeper. Hard-looking problems sometimes transform into known problems with the right math. Currency arbitrage looked domain-specific and complex. After the log transformation, it's just negative cycle detection. Same idea shows up in chess puzzles, chemical kinetics, financial derivatives—if a quantity is multiplicative on a path, take its logarithm and suddenly you have an additive problem solvable by standard algorithms.

Makes you think differently about problem-solving. Always ask: can I transform this into something simpler?

---

## Question 4: Edmonds' Algorithm - Problem Definition

### What Problem Does It Actually Solve?

**Minimum Spanning Arborescence (directed minimal spanning tree)**. Given a directed weighted graph and a root vertex r, find a minimum-weight spanning tree where edges point *toward* the root. Every non-root vertex has exactly one incoming edge. All vertices reachable from the root.

It's the directed version of MST. But the constraint changes everything. In an undirected MST, you pick a cycle-free set of edges. Here, you force a specific structure: one incoming edge per non-root vertex, pointing inward toward the root.

### Why It's Different From MST

Minimum Spanning Tree: undirected, no root, try to minimize total weight. Minimum Spanning Arborescence: directed, rooted structure, minimize weight with directional constraints. Same goal (minimal weight), completely different structure.

### The Algorithm Idea

For each non-root vertex, pick its minimum incoming edge. If no cycles form, done. If cycles exist, contract each cycle into a single node, recursively solve on the contracted graph, then expand back and resolve ties in the contracted edges.

This sounds greedy and wrong. But it works. The cycle contraction mechanism is what preserves optimality globally despite local greedy choices. Counterintuitive but proven.

### Key Insight

In an optimal arborescence, if a non-root vertex v doesn't have its minimum incoming edge selected, you can swap it in without losing optimality. That property makes greedy selection locally correct.

Complexity hits O(VE) naively, optimized to O(E log V) with data structures. Way slower than MST (O(E log E)), but directed graphs need it.

### The Learning

Edmonds' teaches that different problem variants need different solutions. Adding direction changes everything. The algorithm's elegance is in cycle contraction: instead of forbidding cycles outright, embrace them, contract them, and handle them recursively. It's almost beautiful if you squint at the pseudocode long enough.

---

## Question 5: String Matching - KMP and Rabin-Karp

### Compute the LPS Array

Part (a): Build the LPS (Longest Prefix Suffix) array for "ABABCABAB". The LPS at position i tells you: "what's the longest proper prefix of pattern[0..i] that's also a suffix?" Proper means not the whole string.

For "ABABCABAB":
- Position 0: "A" has no proper prefix. LPS[0] = 0.
- Position 3: "ABAB" → prefix "AB" matches suffix "AB". LPS[3] = 2.
- Position 8: "ABABCABAB" → prefix "ABAB" matches suffix "ABAB". LPS[8] = 4.

| Index | Char | Substring | Best Prefix-Suffix Match | LPS |
|-------|------|-----------|--------------------------|-----|
| 0 | A | A | none | 0 |
| 1 | B | AB | none | 0 |
| 2 | A | ABA | "A" matches "A" | 1 |
| 3 | B | ABAB | "AB" matches "AB" | 2 |
| 4 | C | ABABC | none | 0 |
| 5 | A | ABABCA | "A" matches "A" | 1 |
| 6 | B | ABABCAB | "AB" matches "AB" | 2 |
| 7 | A | ABABCABA | "ABA" matches "ABA" | 3 |
| 8 | B | ABABCABAB | "ABAB" matches "ABAB" | 4 |

Final LPS array: [0, 0, 1, 2, 0, 1, 2, 3, 4]

Why does this matter? When the pattern fails to match at position j, instead of restarting from 0, jump to LPS[j-1]. Saves re-checking characters you already know match. That jump is what makes KMP O(N+M) instead of O(N×M).

Building the LPS takes two pointers: one for the current position (i) and one for the length of the matching prefix (len). When pattern[i] == pattern[len], increment len and set LPS[i] = len. When they don't match, fallback to LPS[len-1]. This fallback chain is what makes it work.

### Rabin-Karp: Hashing Instead of Direct Comparison

Instead of comparing characters, use a polynomial rolling hash. hash(s) = (s[0]×BASE^m + s[1]×BASE^(m-1) + ... + s[m-1]) mod MOD. Use BASE=31 for letters, MOD=10^9+9 (big prime).

When you shift the window, update the hash in O(1): new_hash = (old_hash - s[i]×BASE^(m-1)) × BASE + s[i+m]. That's the "rolling" part. You're not recomputing the whole hash; you're adjusting it.

### Collision Handling: The Catch

Hash values collide sometimes. Two different strings hash to the same value. Solution: when hashes match, do a full character-by-character verification. If the strings don't actually match, it's a spurious collision. Move on.

With MOD = 10^9+9, collision probability per window ≈ 1/(10^9+9). Tiny. In practice, this almost never happens, so Rabin-Karp runs O(N+M) on average. Worst case with many collisions? O(N×M).

### Time Complexity Numbers

**KMP**:
- Always O(N+M). No randomness. No worst case.
- Building LPS: O(M)
- Searching: O(N)
- Total: O(N+M)

**Rabin-Karp**:
- Average: O(N+M) (hashing fast, collisions rare)
- Worst: O(N×M) (every window causes collision, forces verification)
- Best: O(N+M) (no hash matches except real ones)

### When to Use Which?

KMP if you need predictable timing. One pattern, guaranteed O(N+M). Rabin-Karp if you have multiple patterns. Hash all k patterns once (O(kM)), scan text once (O(N)), report matches: O(N+kM) total. Running KMP k times would be O(k(N+M)). For many patterns, Rabin-Karp crushes it.

### What Was Surprising

Working through the LPS computation by hand felt tedious. But once I saw the fallback chain (using LPS[len-1] when mismatch happens), the elegance clicked. It's not just a lookup table; it's a failure function that lets you reuse computation.

Rabin-Karp felt like a trick initially. Hashing to avoid character comparison seemed... fragile? But the collision handling makes it rigorous. The probability math makes it work. For my code, I tested both on various strings and they found the same matches, which validated the approach.

### Output Screenshot - Part (a): KMP LPS Array

![alt text](Assignment_2/A2_Q5.png)

---

## Summary and Key Takeaways

### Assignment 1: Containers and Path Algorithms

STL containers aren't just data structures—they're tools with specific performance profiles. Use vector for indexed access, deque when you're battering both ends, array when size is fixed at compile time. Bellman-Ford handles negatives but runs slower than Dijkstra when weights are non-negative. Floyd-Warshall is simple (three loops, one recurrence) but scales poorly. O(V³) grows fast. Both algorithms have their place; pick based on density and constraints.

The overflow bug in Floyd-Warshall was a reminder: INT_MAX is dangerous. Use 1e9 instead.

### Assignment 2: Advanced Algorithms and Strings

Bitmasking works for N ≤ 20 because 2^N becomes tractable. Johnson's algorithm combines two known algorithms with mathematical insight (reweighting) to beat Floyd-Warshall on sparse graphs. That pattern matters: instead of inventing new techniques, combine existing ones cleverly.

Arbitrage detection showed that logarithmic transformation converts multiplicative problems into additive ones. Currency trading became negative cycle detection. That mindset—transforming hard problems into known ones—shows up everywhere.

Edmonds' algorithm for directed MST teaches that directed variants need different solutions. KMP and Rabin-Karp both solve string matching but with different trade-offs. KMP is predictable. Rabin-Karp handles multiple patterns better.

### Programming Reality

1. **Overflow is real**: INT_MAX is not your friend.
2. **Index conversion**: Off-by-one errors hurt. 0-indexed vs 1-indexed conversion needs attention.
3. **Algorithm selection**: Density and constraints matter more than asymptotic complexity.
4. **Problem transformation**: Before coding, ask if the problem can be modeled differently.
5. **STL is your friend**: Modern C++ STL routines (accumulate, sort, etc.) are clean and efficient. Use them.

The assignments forced hands-on engagement with algorithms. Reading about Bellman-Ford and implementing it are different experiences. Debugging the overflow taught me more than any tutorial would.

### What Sticks

Algorithms aren't abstract. They have real trade-offs. Floyd-Warshall is O(V³) but simple. Johnson's is faster on sparse graphs but needs two separate algorithm runs. KMP is deterministic. Rabin-Karp wins with multiple patterns. Problem constraints determine the solution.

Most importantly: testing matters. Sample inputs caught bugs immediately. Verify by hand before trusting output.

---

