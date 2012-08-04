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
                    heapq.heappush (front, (w + ww, nn))
    return dist


n = readints ()[0]
g = {}
for i in range (n):
    for j, v in enumerate (readints ()):
        if i != j:
            g[i] = g.get (i, []) + [(j, v)]

tests = []
s_src = set ()
queries = {}
results = {}

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

for src in s_src:
    dist = None
    new_q = set ()
    for q in queries[src]:
        if src != q:
            new_q.add (q)
        else:
            results[(src, q)] = 0

    if len (new_q) > 0:
        dist = deikstra (g, src, new_q)
        for q in new_q:   
            results[(src, q)] = dist[q]

    


#print results
for src, gas, dest in tests:
    v1 = results[(src, gas)] + results[(gas, dest)]
    v2 = results[(src, dest)]
    print v1, v1-v2
