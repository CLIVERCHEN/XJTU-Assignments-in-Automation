"""
## Code for XJTU Operation Research project
## Analyzing the similarity of a seedset
## -*- coding:utf-8 -*-
"""

def readNodes(list, fileName):
    try:
        with open(fileName, 'r') as file:
            for line in file:
                nodeId = int(line)
                list.append(nodeId)
    except IOError:
        print("failed to open node file")

list_v1 = []
list_v2 = []
readNodes(list_v1, 'a1_output.txt')
readNodes(list_v2, 'a2_output.txt')

similarNum = 0

for i in range(len(list_v1)):
    for j in range(len(list_v2)):
        if list_v1[i] == list_v2[j]:
            similarNum += 1

print("Similarity:", similarNum/max(len(list_v1), len(list_v2)))