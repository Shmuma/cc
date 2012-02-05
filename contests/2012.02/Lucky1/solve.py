import sys


def count_digits (num):
    res4 = res7 = 0
    while num:
        d = num % 10
        if d == 4:
            res4 += 1
        elif d == 7:
            res7 += 1
        num = int (num / 10)
    return res4, res7


def table_generator (n):
    entry = None
    for i in range (1, n+1):
        c4, c7 = count_digits (i)
        if not entry:
            entry = (i, 1, c4, c7)
        else:
            if c4 == entry[2] and c7 == entry[3]:
                entry = (entry[0], entry[1]+1, entry[2], entry[3])
            else:
                yield entry
                entry = (i, 1, c4, c7)
    if entry:
        yield entry


def generate_zero (entry):
    res = []
    a = entry[0]
    b = entry[0] + entry[1]
    for i in range (a, b):
        for j in range (i, b):
            res.append ((i, j))
    return res


def generate (entry_a, entry_b):
    res = []
    for i in range (entry_a[0], entry_a[0] + entry_a[1]):
        for j in range (entry_b[0], entry_b[0] + entry_b[1]):
            res.append ((i, j))
    return res


def sort_pairs (a, b):
    if a[0] != b[1]:
        return a[0] - b[0]
    return a[1] - b[1]


def solve (n):
    res = 0
    table = []
    pairs = []
    for entry in table_generator (n):
        if entry[2] == 0 and entry[3] == 0:
#            print "Zero-group at %d, len %d" % (entry[0], entry[1])
            res += (entry[1] * (entry[1]+1)) / 2
            dat = generate_zero (entry)
            pairs += dat
            assert (len (dat) == (entry[1] * (entry[1]+1)) / 2)
        table.append (entry)
#    print "Len = %d, res = %d" % (len (table), res)
    for i in range (len (table)):
        sum = table[i][2] - table[i][3]
        for j in range (i+1, len (table)):
            sum += table[j][2] - table[j][3]
            if not sum:
#                print "Equal between group at %d, len %d and group at %d, len %d" % (table[i][0], table[i][1], table[j][0], table[j][1])
                if table[i][2] != 0 or table[i][3] != 0:
                    la = 1
                else:
                    la = table[i][1]
                if table[j][2] != 0 or table[j][3] != 0:
                    lb = 1
                else:
                    lb = table[i][1]
                res += la * lb
#                dat = generate (table[i], table[j])
#                pairs += dat
#                assert (len (dat) == la * lb)
    pairs.sort (cmp = sort_pairs)
    for i, j in pairs:
        print i, j
    return res


cases = int (sys.stdin.readline ())

for case in range (cases):
    n = int (sys.stdin.readline ())
    print solve (n)
