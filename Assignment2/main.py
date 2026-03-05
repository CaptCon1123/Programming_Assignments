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

k = 2
m = [1, 1, 2, 3, 1, 3, 3]

print(FIFO(k, m))
print(LRU(k,m))
