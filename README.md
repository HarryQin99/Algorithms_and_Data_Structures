# Algorithms_and_Data_Structures(Unimel 2020/S1)

### Project1
+ Reading data from a csv file, which has over 11 columns and includes many different type of data, and solve the problem of ',' in each column of a csv file, to make sure the data(number/short sentence/long sentence) are correct
+ Using a proper data structure to store all the data read from csv(`struct` and `linked_list`)
+ Searching based on the name of the shop.
+ Writing the search result into the `outfile.txt`, with particular pattern.

### Project2
+ Compared to Project1, in Project2, we employ an advance data structure to store data(same as in Project1), `2-D tree`. We generate the 2-D tree based on the x_coordinate and y_coordinate of each one data point
+ Improve the effiency and time complexity of Searching based on Coordinate
+ Do an experience on how would the allocation of the input data csv affect the height of the  2-D tree we generated, and the effiency of searching.(provided sorted data set, median data set, and ramdom data set)

### Project3
+ Implement an AI Solver to sloving the `Peg Solitaire` game.
+ Based on the pseudocode provided, design the algorithm to solve the game in a accuracy and efficient way and make sure do not have any memory leak on the program.
+ **Note**: Only implement the `ai.c` part, rest of the code are provided by lecturer(or head tutor), note from the spec: The Peg Solitaire game enginge code in this assignment was adapted from the open-source terminal
version made available by Maurits van der Schee1([line](https://github.com/mevdschee/peg-solitaire.c))
