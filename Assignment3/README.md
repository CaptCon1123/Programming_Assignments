Programming Assignment 3
Fernando Hernandez Martin - UFID: 58200371
Connor McFarlin - UFID: 3892-1501

No compiling/building needed. The only dependencies used are glob, time, and matplotlib, all built-in libraries (pip install matplotlib may be needed).

Input and Output Format:
Run the program by directing an input file with "python main.py < input.txt" (make sure you are in the Assignment3 src directory and that you're using a command prompt terminal, not powershell)
You can also just run the script and input with correct format into the terminal line like:
"2
1 
2"

The results are pinted out as well as put into an output.txt file.

Assumptions:
- The request sequence contains exactly m integers.
- All request IDs are integers.
- The cache capacity k ≥ 1.
- Input is provided through standard input (using file redirection).

Solutions to the Written Component:
Question 1:

Question 2:
Let OPT(i,j) represent the maximum total value of any common subsequence between the prefixes A[1..i] and B[1..j], where the value of a subsequence is the sum of the values of its characters.

- Base cases
    If either prefix is empty, then the only common subsequence is the empty subsequence, whose value is 0. Therefore, 
    OPT(0,j) = 0 for all j 
    OPT(i,0) = 0 for all i

- Recurrence
    A[i] and B[j] are the last characters of the two prefixes. If A[i] != B[j], then they cannot be used as the final character of the same common subsequence, so an optimal solution must exclude one of them: 
    OPT(i,j) = max(OPT(i-1,j), OPT(i,j-1))
    Else, if A[i] = B[j], then there exists an optimal solution that uses this character as the last one. Since all character values are nonegative, including this character will only increase or preserve the total value compared to ignoring it. So the best solution comes from taking the best of the smaller prefixes A[1...i-1] and B[1...j-1] then appending this last character:
    OPT(i,j) = OPT(i-1,j-1) + c(A[i])
    Adding the base cases, the full recurrence equation is:
                0                           if i = 0
 OPT(i,j){      0                           if j = 0
                OPT(i-1,j-1) + c(A[i])      if A[i] == B[j]
                max(OPT(i-1,j), OPT(i,j-1)) if A[i] != B[j]

- Proof recurrence is correct:
    If A[i] and B[j] are not equal, then no common subsequence of A[1...i] and B[1...j] can use both of the characters at the same position a the end since they're literally different. So any optimal common subsequence of the two prefixes must exclude either A[i] or B[j]. If it omits A[i], then its value is at most OPT(o-1,j). If it omits B[j] then its value is at most OPT(i,j-1). Since an optimal solution has to do one of these two while maximizing the total vlue, its value will be the max of the two. 

    If A[i] and B[j] are equal, then because character values are nonnegative, there is always an optimal solution that includes this matching character. Any common subsequence of A[0..i-1] and B[0..j-1] can be extended by this character, increasing the total value by c(A[i]). Therefore the best value in this case is the best value on the smaller prefixes plus the value of the matching character.

    Thus the recurrence equation would be optimal/correct in every case.

Question 3:
Create Array arr[0...n][0...m]
for i = 0 to n:
    arr[i][0] = 0
for j = 0 to m:
    arr[0][j] = 0
for i = 1 to n:
    for j = 1 to m:
        if A[i] == B[j]:
            arr[i][j] = arr[i-1][j-1] + c(A[i])
        else:
            arr[i][j] = max(arr[i-1], arr[j-1])
return arr[n][m]

The function 