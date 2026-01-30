Programming Assignment 1
Fernando Hernandez Martin - 58200371
Connor McFarlin: 3892-1501

Input and Output Format:
The input should be in a file called example.in, the input should be formated with the N value on the first line, then followed by N rows of the hospital preferences and N rows of student preferences. The preferences should be a list of the position of the preference seperated by spaces. 

Trend of Runtime Relative to Input Size:
The graph of the increase of the runtime relative to the input size is in runtime_plot.png. As the input size increases, the runtime increases exponentialy for both functions. The runtime of the Gale-Shapley function increases slower than the runtime of the verifier function.


Instructions:
to compile:
g++ -std=c++17 -O2 src/ProgramminAssignment1.cpp -o pa1

match an example:
Get-Content data/example.in | .\pa1 match > data\example.out

verify an example:
Get-Content data/verify_example.in | .\pa1 verify

measure an example:
.\pa1 measure | Out-File results\timings.csv -Encoding utf8

make sure to install matplotlib:
python -m pip install matplotlib

plot your task C measurements (make sure to "cd .." afterwards):
cd results
python plot_timings.py