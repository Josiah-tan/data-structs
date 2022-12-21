from numpy import array


matrix = (
array([[0, 4, 0, 0, 2, 0, 3, 0, 0],
       [0, 3, 0, 0, 0, 9, 0, 7, 5],
       [2, 0, 0, 3, 0, 7, 0, 0, 0],
       [0, 2, 5, 0, 0, 0, 9, 0, 0],
       [3, 0, 0, 0, 6, 0, 0, 0, 2],
       [0, 0, 1, 0, 0, 0, 8, 5, 0],
       [0, 0, 0, 8, 0, 4, 0, 0, 3],
       [7, 8, 0, 1, 0, 0, 0, 2, 0],
       [0, 0, 4, 0, 3, 0, 0, 6, 0]], dtype="object")
)

length = matrix.shape[0]
mini_length = int(length ** 0.5)



def good(current):
    row_number = current // length
    column_number = current % length
    value = matrix[row_number][column_number]
    for i in range(length):
        if (matrix[row_number][i] == value and i != column_number) or (matrix[i][column_number] == value and i != row_number):
            return False

    mini_y = row_number // (length // mini_length)
    mini_x = column_number // (length // mini_length)

    for i in range(length):
        mini_row_number = mini_y * (length // mini_length) + i // mini_length
        mini_column_number = mini_x * (length // mini_length) + i % mini_length
        
        if (matrix[mini_row_number][mini_column_number] == value and mini_row_number * length + mini_column_number != current):
            return False
    return True

    

def solve(current=0):
    if current == length ** 2:
        return 0;
    
    elif matrix[current // length][current % length]:
        return solve(current + 1)

    for j in range(1, length + 1):
        matrix[current // length][current % length] = j
        # print(f"matrix = \n{matrix}")
        if (good(current) and not solve(current + 1)):
            return 0;
            
    matrix[current // length][current % length] = 0
    return 1;

print("impossible" if solve() else "done")
print(matrix)
