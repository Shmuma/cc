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
g = []
for i in range (n):
    g.append (readints ())


for i in range (n):
    for j in range (n):
        for k in range (n):
            v = g[i][k] + g[k][j]
            if g[i][j] > v:
                g[i][j] = v


for m in range (readints ()[0]):
    src, gas, dest = readints ()
    v1 = g[src][gas] + g[gas][dest]
    v2 = g[src][dest]
    print v1, v1-v2
