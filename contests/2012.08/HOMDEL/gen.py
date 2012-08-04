import random

n = 4
m = 10

max_d = 100

print n
for i in range (n):
    d = []
    for j in range (n):
        if i == j:
            d.append (0)
        else:
            d.append (random.randint (1, max_d))
    print " ".join (map (str, d))
print m
for i in range (m):
    s = random.randint (0, n-1)
    g = random.randint (0, n-1)
    d = random.randint (0, n-1)
    print s, g, d

