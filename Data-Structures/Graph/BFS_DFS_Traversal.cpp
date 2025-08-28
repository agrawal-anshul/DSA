/*
================================================================================
COMPLETE GUIDE TO BFS AND DFS GRAPH TRAVERSAL
================================================================================

1. UNDERSTANDING AND VISUALIZATION
----------------------------------

PROBLEM EXPLANATION:
Graph traversal involves visiting every vertex in a graph systematically. Two fundamental 
approaches exist:
- BFS (Breadth-First Search): Explores neighbors level by level (like ripples in water)
- DFS (Depth-First Search): Explores as far as possible along each branch before backtracking

INTUITION BEHIND EACH APPROACH:
- BFS uses QUEUE (FIFO): "Visit all my immediate friends before visiting their friends"
- DFS uses STACK (LIFO): "Go deep into one path until you hit a dead end, then backtrack"

MEMORY AIDS AND NAMING PATTERNS:
- BFS = "Breadth" = "Wide" = Queue = Level-order = Shortest path in unweighted graphs
- DFS = "Depth" = "Deep" = Stack = Pre/In/Post-order = Path finding, cycle detection
- Remember: "B for Breadth, Q for Queue" and "D for Depth, S for Stack"

REPRESENTATIVE EXAMPLE:
Graph structure:
    1 --- 2
   /|     |
  0 |     3
   \|    /
    4 ---

Adjacency List: 0:[1,4], 1:[0,2,4], 2:[1,3], 3:[2,4], 4:[0,1,3]

BFS from 0: 0 -> 1,4 -> 2 -> 3 (level by level)
DFS from 0: 0 -> 1 -> 2 -> 3 -> 4 (deep exploration)

2. BRUTE FORCE APPROACH
-----------------------

NAIVE BFS: Simple queue-based traversal without optimization
- Create visited array, queue, and result vector
- Process each vertex exactly once
- Time: O(V + E), Space: O(V)
- Bottleneck: No major bottlenecks for basic traversal

NAIVE DFS: Simple stack-based or recursive traversal
- Recursive: Use call stack naturally
- Iterative: Explicitly use stack data structure
- Time: O(V + E), Space: O(V + recursion depth)
- Bottleneck: Stack overflow risk in recursive version for deep graphs

3. OPTIMIZATION
---------------

BFS OPTIMIZATIONS:
- Use adjacency list instead of matrix for sparse graphs
- Early termination when target found
- Bidirectional BFS for shortest path between two nodes

DFS OPTIMIZATIONS:
- Iterative approach to avoid stack overflow
- Path compression techniques
- Memoization for repeated subproblems

PERFORMANCE COMPARISON:
| Aspect          | BFS           | DFS (Recursive) | DFS (Iterative) |
|----------------|---------------|-----------------|-----------------|
| Time           | O(V + E)      | O(V + E)        | O(V + E)        |
| Space          | O(V)          | O(V + H)        | O(V)            |
| Stack Overflow | No            | Possible        | No              |
| Path Finding   | Shortest      | Any path        | Any path        |

4. ALGORITHM AND COMPLEXITY ANALYSIS
------------------------------------

BFS ALGORITHM:
1. Initialize queue with start vertex, mark as visited
2. While queue not empty:
   - Dequeue front vertex
   - Process vertex (add to result)
   - For each unvisited neighbor: mark visited and enqueue
3. Return traversal result

DFS ALGORITHM (Iterative):
1. Initialize stack with start vertex
2. While stack not empty:
   - Pop top vertex
   - If not visited: mark visited, process vertex
   - Push all unvisited neighbors to stack
3. Return traversal result

COMPLEXITY ANALYSIS:
- Time Complexity: O(V + E) where V = vertices, E = edges
  - Each vertex visited once: O(V)
  - Each edge examined once: O(E)
- Space Complexity: O(V) for visited array and auxiliary data structure
  - BFS: Queue can hold O(V) vertices in worst case
  - DFS: Stack depth can be O(V) in worst case (linear graph)

5. STEP-BY-STEP WALKTHROUGH
---------------------------

Sample Input: Graph with 5 vertices (0-4) as shown above
Start vertex: 0

BFS Walkthrough:
Step 1: queue=[0], visited=[T,F,F,F,F], result=[]
Step 2: process 0, queue=[1,4], visited=[T,T,F,F,T], result=[0]
Step 3: process 1, queue=[4,2], visited=[T,T,T,F,T], result=[0,1]
Step 4: process 4, queue=[2], visited=[T,T,T,F,T], result=[0,1,4]
Step 5: process 2, queue=[3], visited=[T,T,T,T,T], result=[0,1,4,2]
Step 6: process 3, queue=[], visited=[T,T,T,T,T], result=[0,1,4,2,3]

DFS Walkthrough:
Step 1: stack=[0], visited=[F,F,F,F,F], result=[]
Step 2: pop 0, stack=[4,1], visited=[T,F,F,F,F], result=[0]
Step 3: pop 1, stack=[4,4,2], visited=[T,T,F,F,F], result=[0,1]
Step 4: pop 2, stack=[4,4,3], visited=[T,T,T,F,F], result=[0,1,2]
Step 5: pop 3, stack=[4,4,4], visited=[T,T,T,T,F], result=[0,1,2,3]
Step 6: pop 4, stack=[4,4], visited=[T,T,T,T,T], result=[0,1,2,3,4]
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

class GraphTraversal {
private:
    // Adjacency list representation - vector of vectors for better cache performance
    vector<vector<int>> adjacencyList;
    int vertexCount;
    
    // Helper function to validate vertex bounds
    bool isValidVertex(int vertex) const {
        return vertex >= 0 && vertex < vertexCount;
    }
    
    // Core BFS implementation with detailed state tracking
    void executeBFS(int startVertex, vector<bool>& visited, vector<int>& result) {
        // Queue maintains FIFO order for level-by-level exploration
        queue<int> bfsQueue;
        
        // Initialize the traversal with start vertex
        visited[startVertex] = true;
        bfsQueue.push(startVertex);
        
        // Process vertices level by level until queue is empty
        while (!bfsQueue.empty()) {
            // Get the next vertex to process (FIFO order)
            int currentVertex = bfsQueue.front();
            bfsQueue.pop();
            
            // Add current vertex to traversal result
            result.push_back(currentVertex);
            
            // Explore all adjacent vertices in order
            for (int neighbor : adjacencyList[currentVertex]) {
                // Only process unvisited neighbors to avoid cycles
                if (!visited[neighbor]) {
                    visited[neighbor] = true;  // Mark before enqueueing to avoid duplicates
                    bfsQueue.push(neighbor);
                }
            }
        }
    }
    
    // Recursive DFS implementation - natural and intuitive
    void executeDFSRecursive(int currentVertex, vector<bool>& visited, vector<int>& result) {
        // Mark current vertex as visited and add to result
        visited[currentVertex] = true;
        result.push_back(currentVertex);
        
        // Recursively explore all unvisited neighbors
        for (int neighbor : adjacencyList[currentVertex]) {
            if (!visited[neighbor]) {
                executeDFSRecursive(neighbor, visited, result);
            }
        }
    }
    
    // Iterative DFS implementation - avoids potential stack overflow
    void executeDFSIterative(int startVertex, vector<bool>& visited, vector<int>& result) {
        // Stack maintains LIFO order for depth-first exploration  
        stack<int> dfsStack;
        dfsStack.push(startVertex);
        
        // Process vertices depth-first until stack is empty
        while (!dfsStack.empty()) {
            // Get the next vertex to process (LIFO order)
            int currentVertex = dfsStack.top();
            dfsStack.pop();
            
            // Only process if not yet visited (allows multiple stack entries)
            if (!visited[currentVertex]) {
                visited[currentVertex] = true;
                result.push_back(currentVertex);
                
                // Push all unvisited neighbors to stack (reverse order for consistent traversal)
                for (int i = adjacencyList[currentVertex].size() - 1; i >= 0; i--) {
                    int neighbor = adjacencyList[currentVertex][i];
                    if (!visited[neighbor]) {
                        dfsStack.push(neighbor);
                    }
                }
            }
        }
    }

public:
    // Constructor initializes graph with specified number of vertices
    GraphTraversal(int vertices) {
        vertexCount = vertices;
        adjacencyList.resize(vertices); // Create an empty list for each vertex
    }
    
    // Add undirected edge between two vertices with validation
    void addEdge(int source, int destination) {
        // Validate both vertices before adding edge
        if (!isValidVertex(source) || !isValidVertex(destination)) {
            cout << "Invalid edge: (" << source << ", " << destination << ")\n";
            return;
        }
        
        // Add bidirectional connection for undirected graph
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source);
    }
    
    // BFS traversal starting from specified vertex
    vector<int> breadthFirstSearch(int startVertex) {
        if (!isValidVertex(startVertex)) {
            cout << "Invalid start vertex: " << startVertex << "\n";
            return {};
        }
        
        // Initialize tracking structures
        vector<bool> visited(vertexCount, false);
        vector<int> result;
        result.reserve(vertexCount);  // Optimize memory allocation
        
        // Execute BFS traversal
        executeBFS(startVertex, visited, result);
        return result;
    }
    
    // Complete BFS traversal covering all disconnected components
    vector<int> completeBFS() {
        vector<bool> visited(vertexCount, false);
        vector<int> result;
        result.reserve(vertexCount);
        
        // Process each unvisited vertex to handle disconnected components
        for (int vertex = 0; vertex < vertexCount; vertex++) {
            if (!visited[vertex]) {
                executeBFS(vertex, visited, result);
            }
        }
        return result;
    }
    
    // Recursive DFS traversal starting from specified vertex
    vector<int> depthFirstSearchRecursive(int startVertex) {
        if (!isValidVertex(startVertex)) {
            cout << "Invalid start vertex: " << startVertex << "\n";
            return {};
        }
        
        vector<bool> visited(vertexCount, false);
        vector<int> result;
        result.reserve(vertexCount);
        
        executeDFSRecursive(startVertex, visited, result);
        return result;
    }
    
    // Iterative DFS traversal starting from specified vertex
    vector<int> depthFirstSearchIterative(int startVertex) {
        if (!isValidVertex(startVertex)) {
            cout << "Invalid start vertex: " << startVertex << "\n";
            return {};
        }
        
        vector<bool> visited(vertexCount, false);
        vector<int> result;
        result.reserve(vertexCount);
        
        executeDFSIterative(startVertex, visited, result);
        return result;
    }
    
    // Complete DFS traversal covering all disconnected components
    vector<int> completeDFS() {
        vector<bool> visited(vertexCount, false);
        vector<int> result;
        result.reserve(vertexCount);
        
        for (int vertex = 0; vertex < vertexCount; vertex++) {
            if (!visited[vertex]) {
                executeDFSRecursive(vertex, visited, result);
            }
        }
        return result;
    }
    
    // Utility function to display graph structure
    void displayGraph() const {
        cout << "\nGraph Adjacency List:\n";
        for (int i = 0; i < vertexCount; i++) {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjacencyList[i]) {
                cout << neighbor << " ";
            }
            cout << "\n";
        }
    }
    
    // Utility function to print traversal result
    void printTraversal(const vector<int>& traversal, const string& algorithm) const {
        cout << algorithm << " Traversal: ";
        for (int i = 0; i < traversal.size(); i++) {
            cout << traversal[i];
            if (i < traversal.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }
};

// Main function demonstrating comprehensive testing
int main() {
    cout << "=== GRAPH TRAVERSAL DEMONSTRATION ===\n";
    
    // Create sample graph: 0-1-2-3-4 with additional connections
    //    1 --- 2
    //   /|     |
    //  0 |     3
    //   \|    /
    //    4 ---
    
    GraphTraversal graph(5);
    
    // Build the sample graph
    graph.addEdge(0, 1);  // Connect 0 and 1
    graph.addEdge(0, 4);  // Connect 0 and 4  
    graph.addEdge(1, 2);  // Connect 1 and 2
    graph.addEdge(1, 4);  // Connect 1 and 4
    graph.addEdge(2, 3);  // Connect 2 and 3
    graph.addEdge(3, 4);  // Connect 3 and 4
    
    // Display graph structure
    graph.displayGraph();
    
    cout << "\n=== TRAVERSAL RESULTS FROM VERTEX 0 ===\n";
    
    // Test BFS traversal
    vector<int> bfsResult = graph.breadthFirstSearch(0);
    graph.printTraversal(bfsResult, "BFS");
    
    // Test recursive DFS traversal
    vector<int> dfsRecursiveResult = graph.depthFirstSearchRecursive(0);
    graph.printTraversal(dfsRecursiveResult, "DFS (Recursive)");
    
    // Test iterative DFS traversal
    vector<int> dfsIterativeResult = graph.depthFirstSearchIterative(0);
    graph.printTraversal(dfsIterativeResult, "DFS (Iterative)");
    
    cout << "\n=== COMPLETE TRAVERSALS (ALL COMPONENTS) ===\n";
    
    // Test complete traversals
    vector<int> completeBFSResult = graph.completeBFS();
    graph.printTraversal(completeBFSResult, "Complete BFS");
    
    vector<int> completeDFSResult = graph.completeDFS();
    graph.printTraversal(completeDFSResult, "Complete DFS");
    
    cout << "\n=== TESTING EDGE CASES ===\n";
    
    // Test invalid vertex
    cout << "Testing invalid start vertex:\n";
    vector<int> invalidResult = graph.breadthFirstSearch(10);
    
    // Test single vertex graph
    cout << "\nTesting single vertex graph:\n";
    GraphTraversal singleGraph(1);
    vector<int> singleBFS = singleGraph.breadthFirstSearch(0);
    singleGraph.printTraversal(singleBFS, "Single Vertex BFS");
    
    // Test disconnected graph
    cout << "\nTesting disconnected graph:\n";
    GraphTraversal disconnectedGraph(4);
    disconnectedGraph.addEdge(0, 1);  // Component 1: 0-1
    disconnectedGraph.addEdge(2, 3);  // Component 2: 2-3
    
    vector<int> disconnectedBFS = disconnectedGraph.completeBFS();
    disconnectedGraph.printTraversal(disconnectedBFS, "Disconnected Graph BFS");
    
    cout << "\n=== PERFORMANCE ANALYSIS ===\n";
    cout << "Time Complexity: O(V + E) for both BFS and DFS\n";
    cout << "Space Complexity: O(V) for auxiliary data structures\n";
    cout << "BFS guarantees shortest path in unweighted graphs\n";
    cout << "DFS is memory-efficient for deep graphs\n";
    
    return 0;
}

/*
================================================================================
KEY LEARNING NOTES AND OBSERVATIONS
================================================================================

WHEN TO USE BFS vs DFS:

BFS Applications:
- Finding shortest path in unweighted graphs
- Level-order traversal requirements
- Finding all nodes at distance K
- Social network analysis (friends of friends)
- Web crawling (explore nearby pages first)

DFS Applications:  
- Path finding (any path, not necessarily shortest)
- Cycle detection in graphs
- Topological sorting
- Finding strongly connected components
- Maze solving problems
- Tree/graph structure analysis

IMPLEMENTATION CHOICES:

1. Data Structure Selection:
   - Vector<vector<int>> for adjacency list: Better cache locality than list<list<int>>
   - Queue for BFS: Natural FIFO behavior
   - Stack for iterative DFS: Natural LIFO behavior
   - Vector<bool> for visited: Space-efficient bit packing

2. Memory Optimizations:
   - Reserve capacity for result vectors
   - Use references to avoid copying large data structures
   - Const correctness for read-only operations

3. Error Handling:
   - Vertex validation before operations
   - Graceful handling of invalid inputs
   - Clear error messages for debugging

INTERVIEW TIPS:
- Always clarify if graph is directed or undirected
- Ask about disconnected components handling
- Discuss space-time tradeoffs between approaches
- Mention potential stack overflow in recursive DFS
- Consider early termination optimizations for target searches

COMMON VARIATIONS:
- Modified BFS for shortest path with weights (Dijkstra's algorithm)
- DFS with path tracking for backtracking problems
- Bidirectional search for optimal pathfinding
- Parallel/concurrent implementations for large graphs
*/