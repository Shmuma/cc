import sys
import heapq

def readints ():
    return map (int, sys.stdin.readline ().strip ().split (' '))


def deikstra (g, src, tgt_set):
    dist = {src: 0}
    done = set ([src])
    front = []
    if src in g:
        for n, w in g[src]:
            heapq.heappush (front, (w, n))

    while len (front) > 0:
        w, n = heapq.heappop (front)
        if n in done:
            continue
        dist[n] = w
        done.add (n)
        if done.issuperset (tgt_set):
            break
        if n in g:
            for nn, ww in g[n]:
                if not nn in done:
                    heapq.heappush (front, (nn, w + ww))
    return dist


def solve (g, src, gas, dest):
    pass
#    from_src = deikstra (g, src, set ([gas, dest]))
#    from_gas = deikstra (g, gas, set ([dest]))
#    t1 = from_src[gas] + from_gas[dest]
#    return t1, t1 - from_src[dest]


def heur (g, src, dest):
    if src in g:
        for n, w in g[src]:
            if n == dest:
                return w
    return 10000
 
 
def find_path_len (g, src, dest):
    if (src == dest):
        return 0
    front = []
    if src in g:
        for n, w in g[src]:
            heapq.heappush (front, (heur (g, src, dest) + w, n, w))
    while len (front) > 0:
        h, n, w = heapq.heappop (front)
        if n == dest:
            return w
        if n in g:
            for nn, ww in g[n]:
                heapq.heappush (front, (heur (g, n, nn) + w+ww, nn, w+ww))
    print "path from %d to %d not found" % (src, dest)
    return 10000


n = readints ()[0]
g = {}
for i in range (n):
    for j, v in enumerate (readints ()):
        if i != j:
            g[i] = g.get (i, []) + [(j, v)]

tests = []
s_src = set ()
queries = {}
for m in range (readints ()[0]):
    src, gas, dest = readints ()
    tests.append ((src, gas, dest))
    s_src.add (src)
    s_src.add (gas)

    s = queries.get (src, set ())
    s.add (gas)
    s.add (dest)
    queries[src] = s

    s = queries.get (gas, set ())
    s.add (dest)
    queries[gas] = s

results = {}
for src in s_src:
    dist = deikstra (g, src, queries[src])
    for q in queries[src]:
        results[(src, q)] = dist[q]

#print results
for src, gas, dest in tests:
    v1 = results[(src, gas)] + results[(gas, dest)]
    v2 = results[(src, dest)]
    print v1, v1-v2
