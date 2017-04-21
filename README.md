#8 Puzzle Solver
This project was built to solve the 8 Puzzle using A* as it is the algorithm I am most familiar
with. It makes use of linked lists to form search trees, however my functions could use
improvements. Main.cpp reads in data from in.txt, which provides an initial state and a goal
state, which is then output to out.txt showing the process from the initial state to the goal state.

The linked lists are handled by the tree class. Each connected node has up to 4 children
(middle – 4 | corner – 2 | edge – 3). 2 heuristics are used to build the search tree; firstly, I
take a breadth-depth search approach to construct the tree based on the node with the lowest
distance from the root node. This is then improved with the second heuristic which creates a
cost based on how close to the goal state a current node’s state is, resulting in a smarter
tree that takes care to avoid searching down unnecessary routes (should the program move
backwards or the route lead to more complications, otherwise put as a non-optimal route).
Using a ‘{1 2 34 B 56 7 8|1 2 34 5 6B 7 8}’ state, with just breadth depth applied, the
program took on average 6 minutes to complete. After applying a distance cost heuristic
(A*), the same state was solved in a second, however, there are some states that still
take some time to complete,
‘{1 B 23 4 56 7 8|1 2 34 5 6B 7 8}’ and ‘{7 5 34 B 16 2 8|1 2 34 5 6B 7 8}’ to name
a couple, as they are obviously more complicated and realistic.
