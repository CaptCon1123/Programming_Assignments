from collections import OrderedDict

def FIFO(k, m):
    cache = deque()
    set = set()
    missNum = 0

    for i in m:
        if i not in set:
            if len(cache) >= k:
                oldest = cache.popleft()
                set.remove(oldest)
            
            cache.append(i)
            set.add(i)
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