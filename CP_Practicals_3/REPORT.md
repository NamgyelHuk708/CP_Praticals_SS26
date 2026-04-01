# Technical Report: Graph Algorithms Implementation

---

## Algorithm 1: Floyd-Warshall Algorithm (Negative Cycle Detection)

### a. Problem Summary

The Floyd-Warshall algorithm solves the all-pairs shortest path problem in a weighted directed graph. It computes the shortest distance between every pair of vertices and can detect the presence of negative weight cycles. This algorithm works with graphs containing negative edge weights, making it versatile for various real-world applications like network optimization and cost minimization.

### b. Algorithm Explanation

Floyd-Warshall uses dynamic programming to find shortest paths. The algorithm iterates through all possible intermediate vertices and updates distances whenever a shorter path is discovered through that intermediate vertex.

**Algorithm Steps:**

1. Initialize distance matrix: `dist[i][i] = 0` and `dist[i][j]` equals edge weight or infinity if no direct edge exists.

2. For each intermediate vertex k, source vertex i, and destination vertex j:
   - If path i→k→j is shorter than i→j, update the distance.

3. After completion, check for negative cycles: if any `dist[i][i] < 0`, a negative cycle exists.

### c. Time Complexity Analysis

**Time Complexity: O(n³)**

The algorithm executes three nested loops iterating from 0 to n-1, resulting in n × n × n = n³ operations. This makes Floyd-Warshall suitable for graphs with up to a few hundred vertices.

### d. Space Complexity Analysis

**Space Complexity: O(n²)**

The primary space requirement comes from the distance matrix, which is a two-dimensional array of size n × n. Additionally, auxiliary variables for loop counters and temporary values require constant space O(1). Therefore, the overall space complexity is dominated by the distance matrix, resulting in O(n²) space usage.

### e. Reflection on Implementation and Learning

The implementation of Floyd-Warshall demonstrated the power of dynamic programming. The key insight was understanding that checking all possible intermediate vertices systematically guarantees finding shortest paths. Implementing negative cycle detection revealed how the algorithm could serve dual purposes: computing shortest paths while simultaneously detecting negative cycles. The programmer discovered that examining the diagonal of the final distance matrix efficiently identifies pathological conditions in the graph structure.

### Screenshot

![alt text](image/FWA.png)

**Output Explanation:**
- Initial Distance Matrix shows the graph's edge weights and INF values where no direct edges exist
- Shortest Path Matrix displays computed shortest distances between all vertex pairs after algorithm execution
- The algorithm detected no negative cycles in this example graph
- Sample shortest paths are shown: vertex 0 to 2 costs 8, vertex 1 to 3 costs 4, and vertex 3 to 1 costs 7

---

## Algorithm 2: Johnson's Algorithm

### a. Problem Summary

Johnson's algorithm also solves the all-pairs shortest path problem but optimizes performance for sparse graphs where the number of edges is relatively small compared to the total possible edges. It combines the Bellman-Ford algorithm for handling negative weights with Dijkstra's algorithm for efficiency. The algorithm reweights edges to eliminate negative weights while preserving shortest path relationships, enabling the use of faster Dijkstra algorithm from each vertex.

### b. Algorithm Explanation

Johnson's algorithm elegantly combines two classic shortest-path algorithms through a reweighting technique. The algorithm operates in five main phases:

**Phase 1: Auxiliary Vertex Addition**
An auxiliary vertex is introduced with zero-weight edges connecting to all existing vertices in the graph.

**Phase 2: Bellman-Ford Execution**
Bellman-Ford algorithm runs from the auxiliary vertex to compute a potential value h[v] for each vertex v. These potential values represent the shortest distance from the auxiliary vertex to each vertex.

**Phase 3: Edge Reweighting**
Each original edge (u, v) with weight w is reweighted to: `new_weight = w + h[u] - h[v]`. This transformation ensures all edge weights become non-negative while preserving shortest path relationships. The reweighting formula is mathematically proven to maintain shortest path properties through the triangle inequality.

**Phase 4: Dijkstra Execution**
Dijkstra's algorithm runs from each vertex on the reweighted graph. Since all weights are now non-negative, Dijkstra's efficient algorithm can be applied.

**Phase 5: Distance Recovery**
The computed distances are converted back to original weight space by reversing the reweighting formula: `original_distance = reweighted_distance + h[destination] - h[source]`.

**Key Advantage:** The reweighting mechanism is elegant because it fundamentally transforms the graph without changing the shortest paths themselves, only their representation.

### c. Time Complexity Analysis

**Time Complexity: O(V² log V + VE)**

Breaking down the complexity:
- Bellman-Ford execution: O(VE)
- Dijkstra execution from each of V vertices: V × O(E log V) = O(VE log V)
- Total: O(VE + VE log V) = O(VE log V)

However, in the standard analysis with V iterations of Dijkstra's algorithm implemented with binary heaps, the complexity is approximately O(V² log V + VE). For sparse graphs where E is close to V, this becomes approximately O(V² log V), which is significantly better than Floyd-Warshall's O(V³) complexity.

### d. Space Complexity Analysis

**Space Complexity: O(VE)**

The space usage consists of:
- Adjacency list representation of the graph: O(V + E)
- Potential values array h: O(V)
- Distance matrices and priority queues used during Dijkstra executions: O(V)
- The reweighted adjacency list can have up to E edges: O(E)

The overall space complexity is O(V + E), though with careful implementation storing distance matrices for all vertices simultaneously requires O(V²) space.

### e. Reflection on Implementation and Learning

Implementing Johnson's algorithm revealed sophisticated algorithmic design patterns. The reweighting technique initially appeared confusing, but understanding the mathematical justification through the triangle inequality proved enlightening. The key insight was recognizing that reweighting doesn't change shortest paths, merely their numerical representation. This implementation taught the value of combining algorithms to leverage each algorithm's strengths: using Bellman-Ford's ability to handle negative weights for preprocessing, then exploiting Dijkstra's superior efficiency. Debugging the algorithm required careful attention to the mathematical transformations between weight spaces. Ultimately, Johnson's algorithm demonstrated how clever algorithmic engineering can significantly improve performance for specific input characteristics (sparse graphs), a principle applicable across computer science.

### Screenshot

![alt text](image/JA.png)

**Output Explanation:**
- Displays 4 vertices connected by 6 directed edges with various weights including the cycle (3 to 0)
- The Shortest Path Matrix shows all-pairs shortest distances computed through reweighting and Dijkstra's execution
- Notable results include path from vertex 0 to 2 costing 8 (via vertices 1 and 3), and path from vertex 3 to vertex 1 costing 7
- The algorithm successfully handled the graph's structure and produced identical results to Floyd-Warshall, validating correctness

---

## Algorithm 3: Borůvka's Algorithm (Minimum Spanning Tree)

### a. Problem Summary

Borůvka's algorithm constructs a minimum spanning tree (MST) of a weighted undirected graph. An MST is a subset of edges that connects all vertices without forming cycles, with the minimum possible total edge weight. This algorithm is fundamental in network design, infrastructure planning, and clustering problems where connecting components with minimum cost is essential.

### b. Algorithm Explanation

Borůvka's algorithm builds the MST through a greedy approach by repeatedly selecting minimum-weight edges that connect different components:

**Algorithm Steps:**

1. Initialize each vertex as its own separate component or set.

2. Repeat until only one component remains (when n-1 edges have been added):
   - For each current component, identify the minimum-weight edge that connects this component to any different component
   - Mark all these minimum-weight edges for inclusion
   - Unite the components connected by each marked edge using a Union-Find data structure

3. The collected edges form the minimum spanning tree.

**Union-Find Data Structure:**
Union-Find (also called Disjoint Set Union) efficiently tracks which vertices belong to which component:
- `find(x)` operation returns the representative (root) of the component containing vertex x
- `unite(x, y)` operation merges the components containing vertices x and y
- Path compression and union by rank optimizations ensure near-constant time operations

**Key Insight:** By always selecting the minimum-weight edge from each component to other components, and gradually merging components, Borůvka's algorithm guarantees finding the minimum spanning tree. This greedy approach works because adding the minimum-weight edge from a component cannot be improved by any other choice.

### c. Time Complexity Analysis

**Time Complexity: O(E log V)**

The complexity analysis:
- The algorithm performs at most log V iterations of the outer loop (halving components each iteration in the worst case)
- Each iteration examines all E edges once: O(E)
- Union-Find operations with path compression and union by rank execute in nearly O(1) amortized time
- Total iterations × edge examination: O(E log V)

For dense graphs where E approaches V², this becomes O(V² log V). For sparse graphs where E approaches V, this becomes O(V log V).

### d. Space Complexity Analysis

**Space Complexity: O(V + E)**

Space requirements include:
- Adjacency list or edge list representation: O(V + E)
- Union-Find data structure with parent and rank arrays: O(V)
- Temporary arrays for tracking cheapest edges from each component: O(V)

The overall space complexity is O(V + E), which is linear in the input size, making Borůvka's algorithm very space-efficient.

### e. Reflection on Implementation and Learning

Implementing Borůvka's algorithm provided deep understanding of greedy algorithms and the importance of efficient data structures. The Union-Find implementation, particularly understanding path compression and union by rank optimizations, revealed how subtle implementation details can dramatically affect performance. Initially, implementing the algorithm without these optimizations resulted in slower performance, but adding them achieved near-linear time behavior. The challenge of correctly identifying the minimum-weight edge from each component in each iteration required careful tracking of component representatives. This implementation demonstrated that sometimes the most efficient algorithms achieve their performance through careful engineering rather than clever ideas alone. The comparison with Kruskal's algorithm (sorting all edges and adding them greedily) highlighted how different algorithmic approaches can achieve the same goal with varying efficiency characteristics.

### Screenshot

![alt text](image/BA.png)

**Output Explanation:**
- The graph contains 5 vertices and 7 edges with various weights
- Borůvka's algorithm computed the Minimum Spanning Tree by connecting vertices through the lowest-cost edges
- Final MST includes edges: (0 to 2 weight 2), (1 to 2 weight 1), (3 to 4 weight 2), and (1 to 3 weight 5)
- Total MST weight is 10, achieved with exactly 4 edges connecting 5 vertices (formula: n-1 edges for n vertices)
- Notably, edge (2 to 4 weight 10) was excluded despite existing, confirming the algorithm found the minimum configuration

---

## Comparative Analysis

### Performance Summary

| Characteristic | Floyd-Warshall | Johnson's Algorithm | Borůvka's Algorithm |
|---|---|---|---|
| Problem Type | All-pairs shortest paths | All-pairs shortest paths | Minimum spanning tree |
| Time Complexity | O(n³) | O(n² log n + nm) | O(m log n) |
| Space Complexity | O(n²) | O(n + m) | O(n + m) |
| Negative Weights | Supported | Supported | Not applicable |
| Graph Type | Works on all | Works on all | Undirected graphs |
| Best For | Dense graphs, small n | Sparse graphs | Any graph size |
| Cycle Detection | Yes | Yes | No (creates tree) |

### Selection Criteria

When choosing among these algorithms, practitioners should consider:
- **Problem requirements:** Are all-pairs shortest paths needed or just an MST?
- **Graph characteristics:** Is the graph sparse or dense? What is the edge-to-vertex ratio?
- **Negative weights:** Does the graph contain negative edge weights?
- **Scale:** How many vertices and edges are present?

---

## Conclusion

These three algorithms represent fundamental approaches to graph problems:

1. **Floyd-Warshall** excels at finding shortest paths in small to medium-sized graphs and provides built-in negative cycle detection.

2. **Johnson's algorithm** optimizes for sparse graphs by combining Bellman-Ford's generality with Dijkstra's efficiency through clever reweighting.

3. **Borůvka's algorithm** efficiently computes minimum spanning trees, essential for network design and infrastructure problems.

Each algorithm demonstrates different problem-solving techniques: dynamic programming, algorithm composition, and greedy approaches. Understanding these algorithms provides foundational knowledge for tackling numerous real-world optimization problems across computer science and engineering domains.

---

**Date:** April 1, 2026  
**Subject:** Comparative Analysis of Graph Algorithms  
**Implementation Language:** C++
