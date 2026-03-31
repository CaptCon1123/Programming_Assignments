def findSubString(K, x, A, B):
    n, m = len(A), len(B)

    sub = [[0] * (m + 1) for i in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if A[i - 1] == B[j - 1]:
                sub[i][j] = sub[i - 1][j - 1] + x[A[i - 1]]
            else:
                sub[i][j] = max(sub[i - 1][j], sub[i][j - 1])

    i, j = n, m
    subseq = []

    while i > 0 and j > 0:
        if A[i - 1] == B[j - 1]:
            subseq.append(A[i - 1])
            i -= 1
            j -= 1
        else:
            if sub[i - 1][j] >= sub[i][j - 1]:
                i -= 1
            else:
                j -= 1

    subseq.reverse()

    return sub[n][m], subseq



if __name__ == "__main__":
    K = 3
    x = {'a': 2, 'b': 4, 'c': 5}
    A = "aacb"
    B = "caab"

    maxV, sub = findSubString(K, x, A, B)
    print(maxV)
    print(sub)

    K = 3
    x = {'a': 2, 'b': 4, 'c': 5}
    A = "caab"
    B = "aacb"

    maxV, sub = findSubString(K, x, A, B)
    print(maxV)
    print(sub)

    K = 3
    x = {'a': 1, 'p': 1, 'l': 1, 'e': 1, 'n': 1, 't': 1}
    A = "apple"
    B = "planet"

    maxV, sub = findSubString(K, x, A, B)
    print(maxV)
    print(sub)

    K = 3
    x = {'a': 1, 'p': 1, 'l': 1, 'e': 1, 'n': 1, 't': 1}
    A = "planet"
    B = "apple"

    maxV, sub = findSubString(K, x, A, B)
    print(maxV)
    print(sub)