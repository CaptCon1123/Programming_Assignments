import time
import glob

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

    return sub[n][m], "".join(subseq) # return as string just to make it easier




def readInputFile(path):
    with open(path, "r", encoding="utf-8-sig") as f:
        lines = [line.strip() for line in f.readlines() if line.strip()]

    idx = 0
    K = int(lines[idx]); idx += 1

    charValues = {}
    for i in range(K):
        ch, val = lines[idx].split()
        charValues[ch] = int(val)
        idx += 1

    A = lines[idx]; idx += 1
    B = lines[idx]

    return K, charValues, A, B



def testTime():
    results = []
    for path in sorted(glob.glob("inputs/*.txt")):
        K, charValues, A, B = readInputFile(path)

        start = time.perf_counter()
        maxValue, subseq = findSubString(K, charValues, A, B)
        end = time.perf_counter()

        runtimems = (end - start) * 1000
        results.append((path, runtimems, maxValue, subseq))

        print(f"{path}: {runtimems:.3f} ms")

    files = [r[0] for r in results]
    times = [r[1] for r in results]

    plt.plot(range(len(times)), times, marker='o')
    plt.xlabel("Input File")
    plt.ylabel("Runtime (ms)")
    plt.title("Runtime Across Test Files")
    plt.grid(True)
    plt.show()

    return results






if __name__ == "__main__":
    import matplotlib.pyplot as plt

    results = testTime()

    

