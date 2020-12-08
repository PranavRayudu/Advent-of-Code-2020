import sys

# https://adventofcode.com/2020/day/7


nodes = {}

for desc in sys.stdin:

    desc = desc.replace("bags", "").replace("bag", "").replace(".", "")
    src, contains = desc.split("contain")

    src = src.strip()
    contains = contains.strip().split(", ")
    contains = [c.strip() for c in contains]

    if contains[0] == "no other":
        contains = []
    
    # print(src, contains)    
    nodes[src] = contains


def connected(src, dest):
    if src == dest:
        return True
    for edge in nodes[src]:
        if connected(edge[2:], dest):
            return True
    return False


connections = 0
for node in nodes:
    if (node != "shiny gold" and connected(node, "shiny gold")):
        connections += 1


print(connections)
