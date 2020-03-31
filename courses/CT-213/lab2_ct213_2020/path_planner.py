from grid import Node, NodeGrid
from numpy import inf
import heapq


class PathPlanner(object):
    """
    Represents a path planner, which may use Dijkstra, Greedy Search or A* to plan a path.
    """
    def __init__(self, cost_map):
        """
        Creates a new path planner for a given cost map.

        :param cost_map: cost used in this path planner.
        :type cost_map: CostMap.
        """
        self.cost_map = cost_map
        self.node_grid = NodeGrid(cost_map)

    @staticmethod
    def construct_path(goal_node):
        """
        Extracts the path after a planning was executed.

        :param goal_node: node of the grid where the goal was found.
        :type goal_node: Node.
        :return: a tuple containing the path as a sequence of (x, y) positions: [(x1,y1),(x2,y2),(x3,y3),...,(xn,yn)] and its total cost
        :rtype: list of tuples.
        """
        node = goal_node
        # Since we are going from the goal node to the start node following the parents, we
        # are transversing the path in reverse
        reversed_path = []
        # Lambda function that calculates the distance between two adjacents nodes
        h = lambda start, goal: start.distance_to(goal.i, goal.j)
        # Cost of the path
        cost = 0
        while node is not None:
            reversed_path.append(node.get_position())
            # Here is added the distance between a node and its parent to the cost
            cost += 0 if not node.parent else h(node,node.parent)
            node = node.parent
        # We return a tuple with the past and its cost
        return reversed_path[::-1], cost  # This syntax creates the reverse list

    def dijkstra(self, start_position, goal_position):
        """
        Plans a path using the Dijkstra algorithm.

        :param start_position: position where the planning stars as a tuple (x, y).
        :type start_position: tuple.
        :param goal_position: goal position of the planning as a tuple (x, y).
        :type goal_position: tuple.
        :return: the path as a sequence of positions and the path cost.
        :rtype: list of tuples and float.
        """
		# The first return is the path as sequence of tuples (as returned by the method construct_path())
		# The second return is the cost of the path

        # Lambda function that represents the heuristic function to estimate a distance between two nodes
        h = lambda start, goal: start.distance_to(goal.i, goal.j)
        # Priority queue
        pq = []
        # Start and goal converted to the class Node
        start, goal = self.node_grid.grid[start_position], self.node_grid.grid[goal_position]
        # The distance from a node to itself is zero
        start.g = 0
        # First element added to the heap is the first node
        heapq.heappush(pq, (start.g, start))
        while pq:
            # We pop the closest element in the heap
            cost, node = heapq.heappop(pq)
            # We close this node
            node.closed = True
            for sucessor in self.node_grid.get_successors(node.i, node.j):
                # Convert sucessor to the class Node
                sucessor = self.node_grid.grid[sucessor]
                # If the node wasn't already pushed into the heap, we test it
                if not sucessor.closed:
                    # Close it
                    sucessor.closed = True
                    # Update its distance
                    if sucessor.g > cost + h(node, sucessor):
                        sucessor.g = cost +  h(node, sucessor)
                        sucessor.parent = node
                    # Push it into the heap
                    heapq.heappush(pq, (sucessor.g, sucessor))
        # Get path
        ans = self.construct_path(goal)
        self.node_grid.reset()
        return ans

    def greedy(self, start_position, goal_position):
        """
        Plans a path using greedy search.

        :param start_position: position where the planning stars as a tuple (x, y).
        :type start_position: tuple.
        :param goal_position: goal position of the planning as a tuple (x, y).
        :type goal_position: tuple.
        :return: the path as a sequence of positions and the path cost.
        :rtype: list of tuples and float.
        """

		# The first return is the path as sequence of tuples (as returned by the method construct_path())
		# The second return is the cost of the path

        # Lambda function that represents the heuristic function to estimate a distance between two nodes
        h = lambda start, goal: start.distance_to(goal.i, goal.j)
        # Priority queue
        pq = []
        # Start and goal converted to the class Node
        start, goal = self.node_grid.grid[start_position], self.node_grid.grid[goal_position]
        # Estimates answer
        start.g = h(start, goal)
        # Push it into the heap
        heapq.heappush(pq, (start.g, start))
        while pq:
            # Pop the closest
            cost, node = heapq.heappop(pq)
            node.closed = True
            for sucessor in self.node_grid.get_successors(node.i, node.j):
                sucessor = self.node_grid.grid[sucessor]
                if not sucessor.closed:
                    sucessor.closed = True
                    sucessor.parent = node
                    if sucessor == goal:
                        ans = self.construct_path(goal)
                        self.node_grid.reset()
                        return ans
                    sucessor.g = h(sucessor, goal)
                    heapq.heappush(pq, (sucessor.g, sucessor))

        ans = self.construct_path(goal)
        self.node_grid.reset()
        return ans

    def a_star(self, start_position, goal_position):
        """
        Plans a path using A*.

        :param start_position: position where the planning stars as a tuple (x, y).
        :type start_position: tuple.
        :param goal_position: goal position of the planning as a tuple (x, y).
        :type goal_position: tuple.
        :return: the path as a sequence of positions and the path cost.
        :rtype: list of tuples and float.
        """
		# The first return is the path as sequence of tuples (as returned by the method construct_path())
		# The second return is the cost of the path

        # Lambda function that represents the heuristic function to estimate a distance between two nodes
        h = lambda start, goal: start.distance_to(goal.i, goal.j)
        # Priority queue
        pq = []
        # Start and goal converted to the class Node
        start, goal = self.node_grid.grid[start_position], self.node_grid.grid[goal_position]
        # h(n) + g(n)
        start.f = h(start, goal)
        # The distance from a node to itself is zero
        start.g = 0
        heapq.heappush(pq, (start.f, start))
        while pq:
            cost, node = heapq.heappop(pq)
            node.closed = True
            if node == goal:
                ans = self.construct_path(goal)
                self.node_grid.reset()
                return ans   
            for sucessor in self.node_grid.get_successors(node.i, node.j):
                sucessor = self.node_grid.grid[sucessor]
                if not sucessor.closed:
                    # Use the estimative to update distance
                    if sucessor.f > node.g + h(node,sucessor) + h(sucessor, goal):
                        sucessor.g = node.g + h(node, sucessor)
                        sucessor.f = sucessor.g + h(sucessor,goal)
                        sucessor.parent = node
                        heapq.heappush(pq, (sucessor.f, sucessor))
                        
        ans = self.construct_path(goal)
        self.node_grid.reset()
        return ans
