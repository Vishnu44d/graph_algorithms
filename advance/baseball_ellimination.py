import pandas as pd
import numpy as np
from ford_fulkerson import Graph

inf = 999

# reading the ques.csv file to get the input.
df = pd.read_csv("ques.csv", sep="\t")
df = df.set_index("Team")

# calulating the graph parameters
no_pairs = sum([i for i in range(len(df)-1)])
# print(no_pairs)
no_of_nodes = no_pairs + len(df) + 1
sourse = 0
sink = no_of_nodes-1

# creating the empty graph
graph = [[0 for _ in range(no_of_nodes)] for _ in range(no_of_nodes)]

# creating gij values from input csv file
gij = df[df.columns[3:]]
gij = gij.values

for i in range(len(gij)):
    for j in range(len(gij)):
        if gij[i][j] == '?':
            gij[i][j] = 0
        else:
            gij[i][j] = int(gij[i][j])


# calculating the wi value and to_play values
wi = df["Wins"].values
gi = df["ToPlay"].values

# choose the team, you want to determine the ellimination
print("Choose your team")
for i in range(len(df.columns[3:])):
    print(i, " ", df.columns[3:][i]) 

team = int(input())

#team = 4
# calculating the mx value for the team
m = wi[team]+gi[team]

# updating the gij, wi and gi values according to the selected team
gij = np.delete(gij, (team), axis=0)
wi = np.delete(wi, (team), axis=0)
gi = np.delete(gi, (team), axis=0)

# creating sourse to domain (no of pair) link
fill_gij_value = []
to_fill_graph = []
for k in range(len(gij)):
    for l in range(k+1, len(gij)):
        to_fill_graph.append((k, l))
        fill_gij_value.append(gij[k][l])
for i in range(no_pairs):
    graph[sourse][i+1] = fill_gij_value[i]

# creating team to target link
for i in range(len(df)-1):
    graph[no_pairs+i+1][sink] = m-wi[i]

# filling infinity to all other edges
# i.e. links between domain and codomain.


for i in range(len(to_fill_graph)):
    #print(i)
    graph[i+1][1+to_fill_graph[i][0]+no_pairs]=inf
    graph[i+1][1+to_fill_graph[i][1]+no_pairs]=inf

g = Graph(graph)

calculated_flow = g.FordFulkerson(sourse, sink)
required_flow = sum(fill_gij_value)


print ("The maximum possible flow is ", calculated_flow)
print("The reqired flow is: ", required_flow)
if calculated_flow < required_flow:
    print("Team {} is elliminated.".format(df.columns[3:][team]))
else:
    print("Team {} still have hope.".format(df.columns[3:][team]))

'''
for i in graph:
    print(i)
'''

