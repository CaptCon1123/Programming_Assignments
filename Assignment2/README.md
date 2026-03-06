Programming Assignment 2
Fernando Hernandez Martin - UFID: 58200371
Connor McFarlin - UFID: 3892-1501

No compiling/building needed. The only dependency used is collections, a built in library.

Input and Output Format:
Run the program by directing an input file with "python main.py < input.txt" (make sure you are in the Assignment2 directory and that you're using a command prompt terminal, not powershell)
You can also just run the script and input with correct format into the terminal line like:
"2 7
1 1 2 3 1 3 3 "

The results are pinted out as well as put into an output.txt

Assumptions:
- The request sequence contains exactly m integers.
- All request IDs are integers.
- The cache capacity k ≥ 1.
- Input is provided through standard input (typically using file redirection).

Solutions to the Written Component:

Question 1:
Table:
_____________________________________________________
Input File   |  k   |  m  |  FIFO |  LRU  |  OPTFF  |
File1        |  5   |  80 |  48   |  46   |  30     |
File2        |  4   |  80 |  8    |  8    |  8      |
File3        |  6   |  90 |  54   |  48   |  30     |
____________________________________________________|

- OPTFF produced the fewest cache misses on two of the three input files. On File2, all three policies resulted in the same number of misses. This is expected because OPTFF is the optimal offline algorithm and therefore cannot have more misses than the other policies.

- LRU generally performed better than FIFO. On File1 and File3, FIFO had more misses than LRU (2 and 6 more misses respectively), while both policies had the same number of misses on File2. This occurs because LRU uses recent access history to predict future requests, while FIFO evicts items solely based on insertion order and may remove frequently used items.

* In File2, we believe all policies performed identically because the request sequence repeatedly accessed a set of four items while the cache capacity was also four. Once the cache was filled, all subsequent accesses resulted in hits.

Question 2:
For k = 3, the request sequence 2, 1, 3, 4, 3, 2 results in fewer misses with OPTFF than both LRU and FIFO. Specifically it has 5 misses with LRU and FIFO, and only 4 misses with OPTFF.
The difference occurs when the request 4 is processed since the cache contains 2,1,3 and both FIFO & LRU will evict 2, which they'll need again. OPTFF knows the future values, so it will evict 1 since it will not be used again. This prevents the final request to 2 from causing a miss under OPTFF.

Question 3:
