import itertools
import numpy as np

matrix = np.array([
    [7, 0, 4, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 0, 0, 0, 0, 2],
    [0, 0, 0, 2, 0, 4, 0, 3, 0],
    [0, 0, 7, 0, 0, 6, 0, 8, 9],
    [0, 0, 3, 7, 0, 5, 4, 0, 0],
    [8, 1, 0, 4, 0, 0, 2, 0, 0],
    [0, 5, 0, 6, 0, 1, 0, 0, 0],
    [4, 0, 0, 0, 0, 0, 6, 0, 0],
    [0, 0, 0, 0, 0, 0, 9, 0, 3],
    ])

height = matrix.shape[0]
width = matrix.shape[1]

mini_height = int(height ** 0.5)
mini_width = int(width ** 0.5)



def okay(index):
    current_row = index // width
    current_column = index % width
    value = matrix[current_row][current_column]
    
    # looping through the row
    for j in range(width):
        if j != current_column and matrix[current_row][j] == value:
            return False;

    # looping through the column
    for i in range(height):
        if i != current_row and matrix[i][current_column] == value:
            return False;
   
    # looping through the mini matrix:

    mini_row = (current_row // mini_height) * mini_height
    mini_column = (current_column // mini_width) * mini_width

    for (x, y) in itertools.product(range(mini_width), range(mini_height)):
        i = mini_row + y
        j = mini_column + x
        if (i, j) != (current_row, current_column) and matrix[i][j] == value:
            return False;
    return True

def solve(index):
    print(f"matrix = \n{matrix}")
    if index == height * width:
        return False
    if matrix[index // width][index % width] != 0:
        return solve(index+1)
    for i in range(1, height + 1):
        matrix[index // width][index % width] = i
        if okay(index) and not solve(index + 1):
            return False
    matrix[index // width][index % width] = 0
    return True;

print("impossible" if solve(0) else matrix)
