# https://adventofcode.com/2020/day/1

from sys import stdin

entries = []

for line in stdin:
    entries.append(int(line))

# entries.sort()


def find_sum(tgt):
    a, b, c = 0, 0, 0
    for i in range(len(entries)):
        a = entries[i]
        for j in range(i + 1, len(entries)):
            b = entries[j]
            for k in range(j + 1, len(entries)):
                c = entries[k]
                if a + b + c == 2020:
                    return a, b, c

a, b, c = find_sum(2020)
print(a, b, c, a + b + c, a * b * c)
