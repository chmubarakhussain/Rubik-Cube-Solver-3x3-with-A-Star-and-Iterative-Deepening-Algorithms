# Rubik-Cube-Solver-3x3-with-A-Star-and-Iterative-Deepening-Algorthms
The Rubik's Cube is an important test domain for heuristic search that has 10^19 possible  states, making it impossible to store in memory. We are going to compare Iterative-Deepening and A* Algorithms for the  famous Rubik’s cube puzzle. Comparison will be in terms of number of nodes expanded and  optimality of solution found by these search schemes.
A complete configuration of a puzzle consists of 54 space separated digits which give the color 
information on each of the six sides of the cube. A color on each of the nine cubes on a given side 
is a digit from the set {1, 2, 3, 4, 5, 6}. The first 9 digits of these 54 digits specifying the colors of 
the 9 cubes faces on the front side (left-right and top-bottom), the next 9 numbers specifying the 
color information on the back side and then comes the color information of top, bottom, left and 
right sides. The first line of the file will contains the initial configuration (a space separated list of 54 digit 
code of the colors) the second line contains the final configuration. 
