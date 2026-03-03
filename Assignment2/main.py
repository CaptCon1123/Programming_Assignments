
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
    return 0