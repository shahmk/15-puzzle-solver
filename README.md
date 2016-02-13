15-puzzle-solver
=====

##Usage
1. compile the 16puzzle.cpp file using "g++ 16puzzle.cpp" from terminal on a unix machine.
2. run the a.out file using "./a.out" from terminal followed by the method you want to use (1 for bfs, 2 for dfs, 3* for depth limited and 4 for itterative dfs) and the state of the puzzle as a 32 digit number using 2 spaces for each number and an "SS" for the empty space character. e.g. "./a.out 1 0102030405060708091011121314SS15"

*For depth limited a third parameter is necessary for the maxiumam depth to serach. e.g. "./a.out 3 0102030405060708091011121314SS15 12"
