"""
Written by Vicki Allan using Bellman Ford pseudocode
For me, it is easier to write the min cost max flow using adjacency matrices, so that is what this code does
Feel free to do it your way.
"""

from Stable import doMatch

class Graph:

    # An input edge has three components (startNode, endNode, ranking).
    # This creates a combined edge (startNode, endNode, ranking,possibleFLow).  Our possible flow is 1.
    # We should have two edges: one from a->b indicate preference for men and women.
    # If we don't have two edges, one partner found the other unacceptable, so we can ignore that combination
    def combine(self, edge1, edge2):
        if (edge1[0] == edge2[0] and edge1[1] == edge2[1]):
            return (self.vertices.index(edge1[0]), self.vertices.index(edge1[1]), edge1[2] + edge2[2], 1)
        else:
            return None

    # for our matching, we consider the cost of an edge to be the sum of costs for each partner.
    # In this method, we combine individual edges  (from our input rankings) creating a new set of edges.
    def combine_edges(self, edges):
        new_edges = []
        i = 0

        while i + 1 < len(edges):
            e = self.combine(edges[i], edges[i + 1])
            if e is not None:
                new_edges.append(e)
                i += 2
            else:
                i += 1  # skip the edge without a match
        return new_edges

    def create_graph(self, file_tuple):
        self.vertices.append("Source")  # create a list of all vertices
        with open(file_tuple[0]) as f:
            for line in f:
                pieces = line.split(':')
                name = pieces[0].strip()
                self.vertices.append(name)

                if name:
                    priorities = pieces[1].strip().split(',')
                    for i in range(len(priorities)):
                        priorities[i] = priorities[i].strip()
                        # create an edge a->b with cost and flow
                        self.edges.append((name, priorities[i], i + 1, 1))
            f.close()
        proposerCt = len(self.vertices) - 1
        self.proposer_ct = proposerCt
        # repeat for other file preferences,  Notice, I switch the order of the nodes, so the proposer is always first.
        with open(file_tuple[1]) as f:
            for line in f:
                pieces = line.split(':')
                name = pieces[0].strip()
                self.vertices.append(name)


                if name:
                    priorities = pieces[1].strip().split(',')
                    for i in range(len(priorities)):
                        priorities[i] = priorities[i].strip()
                        # create an edge a->b with cost and flow
                        self.edges.append((priorities[i], name, i + 1, 1))
            f.close()
        self.vertices.append("Sink")
        # Sort edges to get those with same to/from nodes together
        self.edges.sort()
        self.edges = self.combine_edges(self.edges)
        sink = len(self.vertices) - 1

        # set up edges as max flow problem
        for p in range(1, proposerCt + 1):
            self.edges.append((0, p, 0, 1))
        for a in range(proposerCt + 1, sink):
            self.edges.append((a, sink, 0, 1))
        self.make_adjacency()

    # from the list of edges, create an adjacency matrix, residual matrix, and cost_matrix
    def make_adjacency(self):
        self.vertex_ct = len(self.vertices)
        self.adjM = []
        while (len(self.adjM) < self.vertex_ct):
            temp = [0 for i in range(self.vertex_ct)]
            self.adjM.append(temp)
        self.cost_array = [list(row) for row in self.adjM]  # careful to get a deep copy

        for edge in self.edges:
            i = int(edge[0])
            j = int(edge[1])

            if i >= self.vertex_ct or j >= self.vertex_ct or i < 0 or j < 0:
                print(f"Not a Proper Input in Edge {i},{j}")
            else:
                self.adjM[i][j] = edge[3]
                self.cost_array[i][j] = edge[2]
                self.cost_array[j][i] = -edge[2]
            self.residual = [list(row) for row in self.adjM]  # careful to get a deep copy

    # print 2 d array a with label
    @staticmethod
    def print2d_array(label, a):
        print(label)
        for i in range(len(a)):
            print("%3d:" % (i), end=' ')
            for j in range(len(a[i])):
                print("%3d" % (a[i][j]), end=' ')
            print()

    # You will need to modify this so it calls Bellman-Ford repeatedly.
    def do_flow(self):
        src, sink = 0, len(self.vertices) - 1
        flow, cost = self.min_cost_max_flow(src, sink)
        print(f"Max flow = {flow}, Min cost = {cost}")

        matching = self.extract_matching()
        print("Matching result:")
        for emp, app in matching:
            print(f"  {emp} ↔ {app}")

    # utility function used to print the matrix dist with label
    def print_array(self, label, dist):
        print(label)
        for i in range(self.vertex_ct):
            print("{0}\t\t{1}".format(i, dist[i]))

    # Finds shortest distances from src to
    # all other vertices using Bellman-Ford algorithm. We assume no negative weight cycles
    # We are interested in the path from the src to the sink.
    # If we never make it to the sink, there is no flow
    # return true if there is flow from src to sink.
    def BellmanFord(self, src, sink):

        # Step 1: Initialize distances from src to all other vertices
        # as INFINITE
        dist = [9999 for i in range(self.vertex_ct)]  # dist/cost to each node
        pred = [-1 for i in range(self.vertex_ct)]  # predecessor of each node
        dist[src] = 0

        # Step 2: Relax all edges |V| - 1 times. A simple shortest
        # path from src to any other vertex can have at-most |V| - 1
        # edges
        for _ in range(self.vertex_ct - 1):
            for u in range(self.vertex_ct):
                for v in range(self.vertex_ct):
                    if self.residual[u][v] > 0 and dist[u] != 9999 and dist[u] + self.cost_array[u][v] < dist[v]:
                        dist[v] = dist[u] + self.cost_array[u][v]
                        pred[v] = u
                        
        self.pred = pred
        #self.print_array("Predecessor", pred)
        #self.print_array("Cost", dist)
        
        return pred[sink] >= 0

    def min_cost_max_flow(self, src, sink):
        flow = 0
        cost = 0
        while self.BellmanFord(src, sink):
            v = sink
            path_flow = float("inf")
            while v != src:
                u = self.pred[v]
                if u == -1:
                    path_flow = 0
                    break
                path_flow = min(path_flow, self.residual[u][v])
                v = u
            if path_flow == 0 or path_flow == float("inf"):
                break
            v = sink
            while v != src:
                u = self.pred[v]
                self.residual[u][v] -= path_flow
                self.residual[v][u] += path_flow
                cost += self.cost_array[u][v] * path_flow
                v = u
            flow += path_flow
        return flow, cost

    def extract_matching(self):
        matches = []
        src, sink = 0, len(self.vertices) - 1
        for u in range(1, self.proposer_ct + 1):
            for v in range(self.proposer_ct + 1, sink):
                if self.adjM[u][v] > 0 and self.residual[u][v] == 0:
                    matches.append((self.vertices[u], self.vertices[v]))
        return matches

    # create an adjacency matrix from men preferencese and women preferences
    def __init__(self, fileTuple):
        self.proposer_ct = None
        self.pred = None
        self.vertices = []
        self.adjM = []
        self.vertex_ct = 0
        self.edges = []
        self.residual = []
        self.cost_array = []
        print("Calling create_graph")
        print(fileTuple)
        self.create_graph(fileTuple)



files = [
    ("Employers1.txt", "Applicants1.txt", False),
    ("Employers2.txt", "Applicants2.txt", False),
    ("Employers3.txt", "Applicants3.txt", False),
    ("Employers4.txt", "Applicants4.txt", False),
    ]
for fileTuple in files:
    print(fileTuple)
    doMatch("Employers propose ", fileTuple, "stable")
    fileList = list(fileTuple)
    fileList[0], fileList[1] = fileList[1], fileList[0]
    fileTuple= tuple(fileList)
    doMatch("Applicants propose ", fileTuple, "stable")
    print("\n")
    g=Graph(fileTuple)
    g.do_flow()
    print("-------------------------------------------------------------------------------\n")

