from collections import deque
from collections import OrderedDict

def FIFO(k, m):
    cache = deque()
    Vset = set()
    missNum = 0

    for i in m:
        if i not in Vset:
            if len(cache) >= k:
                oldest = cache.popleft()
                Vset.remove(oldest)
            
            cache.append(i)
            Vset.add(i)
            missNum += 1


    return missNum

def LRU(k, m):
    cache = OrderedDict()
    missNum = 0

    for i in m:
        if i not in cache:
            if len(cache) >= k:
                cache.popitem(last=False)
            cache[i] = True
            missNum += 1
        else:
            cache.move_to_end(i)

    return missNum

def OPTFF(k, m):
    INF = 10**18
    n = len(m)
    next_idx = [INF] * n
    next_pos = {} 

    for i in range(n - 1, -1, -1):
        x = m[i]
        next_idx[i] = next_pos.get(x, INF)
        next_pos[x] = i
    cache = set()
    nxt = {}   
    missNum = 0

    for i, x in enumerate(m):
        x_next = next_idx[i]

        if x in cache:
            # hit
            nxt[x] = x_next
            continue
        # miss
        missNum += 1
        if len(cache) < k:
            cache.add(x)
            nxt[x] = x_next
            continue
        # cache full
        victim = None
        victim_next = -1
        for item in cache:
            item_next = nxt.get(item, INF)
            if item_next > victim_next:
                victim_next = item_next
                victim = item

        cache.remove(victim)
        nxt.pop(victim, None)
        cache.add(x)
        nxt[x] = x_next
    return missNum

k = 2
m = [1, 1, 2, 3, 1, 3, 3]

print(FIFO(k, m))
print(LRU(k,m))
print(OPTFF(k, m))