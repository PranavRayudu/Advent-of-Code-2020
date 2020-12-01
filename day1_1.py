# https://adventofcode.com/2020/day/1

from sys import stdin

entries = []

for line in stdin:
    entries.append(int(line))

entries.sort()

# print(*entries)

i, j = 0, len(entries) - 1
a, b = 0, 0

while i != j:
    a = entries[i]
    tgt = 2020 - a
    
    while entries[j] > tgt:
        j -= 1

    b = entries[j]

    if a + b == 2020:
        break

    i += 1


print(a, b, a + b, a * b)
