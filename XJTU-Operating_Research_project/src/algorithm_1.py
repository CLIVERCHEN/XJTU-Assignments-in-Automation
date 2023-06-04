"""
## Code for XJTU Operation Research project
## Algorithm_1
## -*- coding:utf-8 -*-
"""

import random
import time
import heapq
import matplotlib.pyplot as plt
import networkx as nx

class Node:
    def __init__(self, id, order):
        self.id = id
        self.order = order
        self.marginalGain = 0
        self.isActive = False
        self.activationProbability = 0.0

    def getId(self):
        return self.id

    def getActivationProbability(self):
        return self.activationProbability

    def setActivationProbability(self, probability):
        self.activationProbability = probability

    def getMarginalGain(self):
        return self.marginalGain

    def setMarginalGain(self, marginalGain):
        self.marginalGain = marginalGain

    def isActiveNode(self):
        return self.isActive

    def activateNode(self):
        self.isActive = True

    def __lt__(self, other):
        return self.marginalGain > other.marginalGain  # Modify the comparison condition to the reverse order of marginal gain


class SocialNetwork:
    def __init__(self, nodeFileName, edgeFileName):
        self.seedSet = set()
        self.pq = []
        self.nodes = {}
        self.edges = {}
        self.readNodes(nodeFileName)
        self.readEdges(edgeFileName)
        random.seed(time.time())

    def pre_Propagation(self, activatedNum):
        for node in self.nodes.values():
            if not node.isActiveNode():
                marginalGain = self.getActivateNum(node) - activatedNum
                node.setMarginalGain(marginalGain)
                node.setActivationProbability(1.0) # set p
                heapq.heappush(self.pq, node)  # put node into heap

    def getActivateNum(self, node = None):
        if node == None:
            activatedNum = self.simulatePropagation(self.seedSet)
            return activatedNum
        else:
            self.seedSet.add(node)
            activatedNum = self.simulatePropagation(self.seedSet)
            self.seedSet.remove(node)
            return activatedNum

    def update(self, node, activatedNum):
        marginalGain = self.getActivateNum(node) - activatedNum
        node.setMarginalGain(marginalGain)
        heapq.heappush(self.pq, node)

    def empty_pq(self):
        self.pq = []

    def analyzePropagation(self, targetNum):
        start = time.time()

        activated_nums = []  # Used to store changes in the number of activated nodes
        seed_nums = []  # Used to store changes in the number of seed nodes

        activatedNum = 0
        self.pre_Propagation(activatedNum)

        while activatedNum < targetNum:
            node = heapq.heappop(self.pq)  # Pop the node with the greatest marginal gain
            self.seedSet.add(node)
            node.activateNode()
            activatedNum += node.getMarginalGain()

            decay = 0
            while True:
                tmpNode = heapq.heappop(self.pq)
                tmpMarginalGain = self.getActivateNum(tmpNode) - activatedNum

                if tmpMarginalGain >= self.pq[0].getMarginalGain() - decay:
                    self.seedSet.add(tmpNode)
                    tmpNode.activateNode()
                    activatedNum = self.getActivateNum()
                    break

                decay += 1

            activated_nums.append(activatedNum)
            seed_nums.append(len(self.seedSet))

            self.empty_pq()
            self.pre_Propagation(activatedNum)

        end = time.time()
        elapsedTime = end - start

        # output seednode's id as txt file
        activatedNodeList = []
        for seed in self.seedSet:
            activatedNodeList.append(seed.getId())

        with open('a1_output.txt', 'w') as file:
            for item in activatedNodeList:
                file.write(str(item) + '\n')

        print("number of seed node:", len(self.seedSet))
        print("number of activated node:", activatedNum)
        print("running time:", elapsedTime, "s")

        # Plot the change in the number of seed nodes versus the number of activated nodes
        plt.figure(figsize=(10, 6))  # resize image
        plt.plot(seed_nums, activated_nums)
        plt.xlabel('Number of Seed Nodes')
        plt.ylabel('Number of Activated Nodes')
        plt.title('Propagation Analysis')
        plt.tight_layout()
        plt.savefig('propagation_analysis.png')  # save image
        plt.show()

        # plot graphic
        G = nx.Graph() # Create graphics objects

        for node_id in self.nodes:
            G.add_node(node_id)
        for edge_from, edges_to in self.edges.items():
            for edge_to in edges_to:
                G.add_edge(edge_from, edge_to)

        fig = plt.figure(figsize=(10, 8), dpi=500)  # set canvas size and resolution
        pos = nx.spring_layout(G, seed=300)  # specify node layout

        nx.draw_networkx_nodes(G, pos=pos, node_color='blue', node_size=2)  # draw nodes
        nx.draw_networkx_edges(G, pos=pos, edge_color='black', width=0.2, alpha=0.8, arrowsize=5)  # draw edges

        # Draw activated nodes and set special styles
        seeds = []
        for seed in self.seedSet:
            seeds.append(seed.getId())
        nx.draw_networkx_nodes(G, pos=pos, nodelist=seeds, node_color='red', node_size=2)

        plt.axis('off')

        plt.title('Network Structure')
        plt.tight_layout()
        plt.savefig('network_structure.png')  # save image

        # show image
        plt.show()

    def readNodes(self, fileName):
        try:
            with open(fileName, 'r') as file:
                tmp_order = 0
                for line in file:
                    nodeId = int(line)
                    node = Node(nodeId, tmp_order)
                    self.nodes[node.getId()] = node
                    tmp_order += 1
        except IOError:
            print("failed to open node file")

    def readEdges(self, fileName):
        try:
            with open(fileName, 'r') as file:
                for line in file:
                    fromNode, toNode = map(int, line.split())
                    if fromNode not in self.edges:
                        self.edges[fromNode] = []
                    self.edges[fromNode].append(toNode)
        except IOError:
            print("failed to open edge file")

    def simulatePropagation(self, seedSet):  # BFS
        visited = set()
        activatedNum = 0
        q = []

        for seed in seedSet:
            q.append(seed)
            visited.add(seed.getId())
            activatedNum += 1

        while q:
            node = q.pop(0)

            if node.getId() in self.edges:
                for neighbor in self.edges[node.getId()]:
                    if neighbor not in visited:
                        probability = random.random()
                        if probability <= self.nodes[neighbor].getActivationProbability():
                            visited.add(neighbor)
                            activatedNum += 1
                            q.append(self.nodes[neighbor])
        return activatedNum

if __name__ == '__main__':
    nodeFileName = "node.txt"
    edgeFileName = "edge.txt"

    socialNetwork = SocialNetwork(nodeFileName, edgeFileName)
    socialNetwork.analyzePropagation(800)
