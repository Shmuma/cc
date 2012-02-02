import sys


def count_digit (digit, num):
    res = 0
    while num:
        if num % 10 == digit:
            res += 1
        num = int (num / 10)
    return res


def count_will_change (digit, num):
    """
    Returns True if amount of digits will change on num+1
    """
    return count_digit (digit, num) != count_digit (digit, num+1)


def change_generator (digit, max_n):
    prev_count = 0
    for n in range (max_n):
        count = count_digit (digit, n)
        yield n, count, prev_count != count
        prev_count = count


def range_count (digit, start, end):
    return sum (map (lambda n: count_digit (digit, n), range (start, end+1)))


def equal_range_generator (end):
    for a in range (end):
        for b in range (a+1):
            if range_count (4, b, a) == range_count (7, b, a):
                yield (b, a)


print list (equal_range_generator (10))

