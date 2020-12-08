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
    
    contains = [(int(c[:2]), c[2:]) for c in contains]
    print(src, contains)
    nodes[src] = contains


def connected(src):
    count = 0
    for c, edge in nodes[src]:
        count += c + c * connected(edge)
    return count


print(connected("shiny gold"))
