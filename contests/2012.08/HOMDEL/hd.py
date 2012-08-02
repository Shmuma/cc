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
    from_src = deikstra (g, src, set ([gas, dest]))
    from_gas = deikstra (g, gas, set ([dest]))
    t1 = from_src[gas] + from_gas[dest]
    return t1, t1 - from_src[dest]


n = readints ()[0]
g = {}
for i in range (n):
    for j, v in enumerate (readints ()):
        if i != j:
            g[i] = g.get (i, []) + [(j, v)]

for m in range (readints ()[0]):
    src, gas, dest = readints ()
    p1, p2 = solve (g, src, gas, dest)
    print p1, p2
