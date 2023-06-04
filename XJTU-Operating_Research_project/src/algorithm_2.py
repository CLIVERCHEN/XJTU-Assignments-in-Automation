"""
## Code for XJTU Operation Research project
## Algorithm_2
## -*- coding:utf-8 -*-
"""

import random
import time
import matplotlib.pyplot as plt
import networkx as nx

class Node:
    def __init__(self, id, order):
        self.id = id
        self.order = order
        self.marginalGain = 0
        self.isActive = False
        self.activationProbability = 0.0
        self.selectTime = 0

    def selectNode(self):
        self.selectTime += 1

    def getSelectTime(self):
        return self.selectTime

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

    def deactivateNode(self):
        self.isActive = False

    def __lt__(self, other):
        return self.marginalGain > other.marginalGain  # Modify the comparison condition to the reverse order of marginal gain


class SocialNetwork:
    def __init__(self, nodeFileName, edgeFileName):
        self.seedSet = set()
        self.pre_sorted = []
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
                node.setActivationProbability(0.2)  # set p
                self.pre_sorted.append(node)
                #heapq.heappush(self.pq, node)  # put node into heap
        self.pre_sorted = sorted(self.pre_sorted)


    def getActivateNum(self, node = None):
        if node == None:
            activatedNum = self.simulatePropagation(self.seedSet)
            return activatedNum
        else:
            self.seedSet.add(node)
            activatedNum = self.simulatePropagation(self.seedSet)
            self.seedSet.remove(node)
            return activatedNum

    def deactivate_node(self):
        for node in iter(self.seedSet):
            node.deactivateNode()

    def empty_pre_sorted(self):
        self.pre_sorted = []

    def analyzePropagation(self, targetNum, iterationNum):
        start = time.time()

        activated_nums = 0.0
        seed_nums = 0.0

        seedList = []
        iterList = []

        activated_nums_list = []
        seed_nums_list = []

        for iteration in range(iterationNum):
            activatedNum = 0
            self.pre_Propagation(activatedNum)

            while activatedNum < targetNum:
                node = self.pre_sorted[0]  # Pop the node with the greatest marginal gain
                self.seedSet.add(node)
                node.activateNode()
                activatedNum += node.getMarginalGain()
                node.selectNode()
                del self.pre_sorted[0]

                decay = 0
                i = 0
                while True:
                    tmpNode = self.pre_sorted[i]
                    tmpMarginalGain = self.getActivateNum(tmpNode) - activatedNum

                    if tmpMarginalGain >= self.getActivateNum(self.pre_sorted[i + 1]) - activatedNum - decay:
                        self.seedSet.add(tmpNode)
                        tmpNode.selectNode()
                        tmpNode.activateNode()
                        activatedNum = self.getActivateNum()
                        del self.pre_sorted[i]
                        break

                    i += 1
                    decay += 1

                activated_nums_list.append(activatedNum)
                seed_nums_list.append(len(self.seedSet))

            activated_nums += activatedNum
            seed_nums += len(self.seedSet)
            print(seed_nums / (iteration + 1))
            seedList.append(seed_nums / (iteration + 1))
            iterList.append(iteration + 1)

            self.deactivate_node()
            self.seedSet.clear()
            self.empty_pre_sorted()

        end = time.time()
        elapsedTime = end - start

        # output node's id as txt file
        tmpList = []
        activatedNodeList = []

        for key in self.nodes:
            tmpList.append((self.nodes[key].getId(), self.nodes[key].getSelectTime()))

        tmpList = sorted(tmpList, key=lambda x: -x[1])

        for i in range(int(seed_nums / iterationNum)):
            activatedNodeList.append(tmpList[i][0])

        with open('a2_output.txt', 'w') as file:
            for item in activatedNodeList:
                file.write(str(item) + '\n')

        # print
        print("number of seed node:", seed_nums/iterationNum)
        print("number of activated node:", activated_nums/iterationNum)
        print("running time:", elapsedTime/iterationNum, "s")

        # Plot the change in the number of seed nodes versus the number of activated nodes
        plt.plot(seed_nums_list, activated_nums_list)
        plt.xlabel('Number of Activated Nodes')
        plt.ylabel('Number of Seed Nodes')
        plt.title('result: Propagation Analysis')
        plt.tight_layout()
        plt.savefig('result_Propagation_Analysis_0.2.png')  # save image

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
        nx.draw_networkx_nodes(G, pos=pos, nodelist=activatedNodeList, node_color='red', node_size=2)

        plt.axis('off')

        plt.title('result: Network Structure')
        plt.tight_layout()
        plt.savefig('result:_network_structure_0.2.png')  # save image
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
        propagation_time = 0

        for seed in seedSet:
            q.append(seed)
            visited.add(seed.getId())
            activatedNum += 1

        size = len(q)

        while q:
            if propagation_time > 8:
                print(propagation_time)
                return activatedNum
            node = q.pop(0)

            if node.getId() in self.edges:
                for neighbor in self.edges[node.getId()]:
                    if neighbor not in visited:
                        probability = random.random()
                        if probability <= self.nodes[neighbor].getActivationProbability():
                            visited.add(neighbor)
                            activatedNum += 1
                            q.append(self.nodes[neighbor])

            size -= 1
            if size == 0:
                propagation_time += 1  # Limit the search depth when BFS (<8)
                size = len(q)

        return activatedNum

if __name__ == '__main__':
    nodeFileName = "node.txt"
    edgeFileName = "edge.txt"

    socialNetwork = SocialNetwork(nodeFileName, edgeFileName)
    socialNetwork.analyzePropagation(800,500)
