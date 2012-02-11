
import itertools


def isprime(n):
    for x in range(2, int(n**0.5)+1):
        if n % x == 0:
            return False
    return True


def check1 (a, b, c, d, e, f, g, h, i, j):
    return (a + b + c + d + e) % 6 == 0


def check2 (a, b, c, d, e, f, g, h, i, j):
    return (f + g + h + i + j) % 5 == 0


def check3 (a, b, c, d, e, f, g, h, i, j):
    return (a + c + e + g + i) % 9 == 0


def check4 (a, b, c, d, e, f, g, h, i, j):
    return (b + d + f + h + j) % 2 == 0


def check56789 (a, b, c, d, e, f, g, h, i, j):
    if (a * 10 + b) % 3 != 0:
        return False
    if (c * 10 + d) % 4 != 0:
        return False
    if (e * 10 + f) % 7 != 0:
        return False
    if (g * 10 + h) % 8 != 0:
        return False
    if (i * 10 + j) % 10 != 0:
        return False
    return True


def check10 (a, b, c, d, e, f, g, h, i, j):
    return all (map (isprime, [n1 * 10 + n2 for n1, n2 in [(f, e), (h, c), (j, a)]]))


for perm in itertools.permutations (range (10), 10):
    if perm[0] == 0:
        continue
    if not (check1 (*perm) and check2 (*perm) and check3 (*perm) and check4 (*perm) and check56789 (*perm) and check10 (*perm)):
        continue
    print perm
