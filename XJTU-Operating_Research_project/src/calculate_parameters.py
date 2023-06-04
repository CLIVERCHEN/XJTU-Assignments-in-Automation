"""
## Code for XJTU Operation Research project
## analysis of graph features of social networks
## -*- coding:utf-8 -*-
"""

import networkx as nx

def read_edges_from_file(file_path):
    edges = []
    with open(file_path, 'r') as file:
        for line in file:
            source, target = line.strip().split()
            edges.append((source, target))
    return edges


def calculate_network_parameters(file_path):
    # 从文件中读取边信息
    edges = read_edges_from_file(file_path)

    # 创建有向图对象
    G = nx.DiGraph(edges)

    # 计算平均度数
    average_degree = sum(dict(G.degree()).values()) / nx.number_of_nodes(G)

    # 计算整体集聚系数
    global_clustering_coefficient = nx.transitivity(G.to_undirected())

    # 计算平均集聚系数
    average_clustering_coefficient = nx.average_clustering(G)

    # 计算网络密度
    density = nx.density(G)

    # 计算强连通分量数量
    num_strongly_connected_components = nx.number_strongly_connected_components(G)

    # 计算弱连通分量数量
    num_connected_components = nx.number_connected_components(G.to_undirected())

    return global_clustering_coefficient, average_clustering_coefficient, average_degree, density, num_strongly_connected_components, num_connected_components


file_path = 'edge.txt'
global_clustering_coefficient, average_clustering_coefficient, average_degree, density, num_strongly_connected_components, num_connected_components = calculate_network_parameters(file_path)

print("Average Degree:", average_degree)
print("Global Clustering Coefficient:", global_clustering_coefficient)
print("Average Clustering Coefficient:", average_clustering_coefficient)
print("Network Density:", density)
print("Number of Strongly Connected Components:", num_strongly_connected_components)
print("Number of Connected Components:", num_connected_components)