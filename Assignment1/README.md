Programming Assignment 1
Fernando Hernandez Martin - 58200371
Connor

to compile:
g++ -std=c++17 -O2 src/ProgramminAssignment1.cpp -o pa1

match an example:
Get-Content data/example.in | .\pa1 match > data\example.out

verify an example:
Get-Content data/verify_example.in | .\pa1 verify

measure an example:
.\pa1 measure | Out-File results\timings.csv -Encoding utf8