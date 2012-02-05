
# solve the task using brute force approach
n = 100
res = 0

cache = {}

def count_digits (num):
    global cache

    if num in cache:
        return cache[num]
    orig_num = num
    res4 = res7 = 0
    while num:
        d = num % 10
        if d == 4:
            res4 += 1
        elif d == 7:
            res7 += 1
        num = int (num / 10)
    cache[orig_num] = res4, res7
    return res4, res7


def is_ok (a, b):
    c4 = c7 = 0
    for i in range (a, b+1):
        d4, d7 = count_digits (i)
        c4 += d4
        c7 += d7
    return c4 == c7


for i in range (1, n+1):
    for j in range (i, n+1):
       if is_ok (i, j):
           print i, j
           res += 1

print res
